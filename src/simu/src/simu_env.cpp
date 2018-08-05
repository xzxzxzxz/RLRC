/********************************************************
  Autonomous Driving Software
  Copyright (c) 2018 MSC Lab, UC Berkeley 
  All rights reserved.
  written by Baiyu Peng
 ********************************************************/

// ROS Includes

#include <ros/ros.h>

// User defined includes
#include "dbw_mkz_msgs/SteeringReport.h"
#include "dbw_mkz_msgs/SteeringCmd.h"
#include "path_follower/state_Dynamic.h"
#include "geometry_msgs/TwistStamped.h"

// cpp includes
#include <cmath>
#include<iostream>
#include<algorithm>

using namespace std;
//To do: define global variable 
dbw_mkz_msgs::SteeringReport steeringreport;
dbw_mkz_msgs::SteeringCmd steeringcmd;
path_follower::state_Dynamic statedynamic;
geometry_msgs::TwistStamped twistcmd;


float state[7]={0},nextstate[7]={0},action[2],dt,maxSteeringRate,maxDvxdt;
    float pi=3.1415926,X,Y,phi,v_x,v_y,r,d_f,dvxdt,a,b,m,I_z,a0,Crr,trMdlFront,trMdlRear,Bf,Cf,Df,Ef,Br,Cr,Dr,Er,g,Fnr,Fnf,a_f,a_R,FyF,a_F,FxR,realFxR,F_ext[2];
    float	steering,steeringRatio,maxSteering,trMdl[4],vhMdl[4],TM_param_f[4],TM_param_r[4],FyR_paj, FyR_max, Fy[2], FyR,dvydt ,drdt,r_next,X_next,Y_next ,v_y_next , phi_next,v_x_next,F_side,u[2];
    int idx;

float sign(float k){
	if (k<0) return -1;
	if (k>0) return 1;
	return 0;
}

void cmd_vel_stampedCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
   action[0]=(msg->twist.linear.x-state[3])/dt/maxDvxdt;
}

void steering_cmdCallback(const dbw_mkz_msgs::SteeringCmd::ConstPtr& msg)
{
   int temp,temp2;
   temp2 = msg->steering_wheel_angle_cmd;
   temp = msg->steering_wheel_angle_velocity;
   action[1] = min(temp/maxSteeringRate,abs(state[6]*steeringRatio-temp2)/dt);
   if (temp==0) action[1]=1;
   action[1]=action[1]*sign(temp2-state[6]*steeringRatio);
}


void f_6s(){

//   process model
//    input: z: state z at time k, z := [X, Y, phi, v_x, v_y, r]
//           u: input u at time k, u := [d_f, dvxdt]
//           vhMdl: vehicle model
//           trMdl: tire model
//           F_ext: friction/resistance
//           F_side: the side force on the vehicle, direction: Y axis
//           dt: timestep length
//    output: state at next time step z[k+1]
//            a_F: slip angle (angle btw tire speed and orientation)
//    """
                                                                     
// get states / inputs                                             
    X     = state[0];                                                         
    Y     = state[1];                                                            
    phi   = state[2];                                                     
    v_x   = state[3];                                                    
    v_y   = state[4];
    r     = state[5];
    d_f   = u[0];
    dvxdt = u[1];

//prevent negative longitudinal speed
    v_x_next =v_x +dt*dvxdt;
    if (v_x_next < 0)
       {
	   dvxdt = - v_x / dt;
        v_x_next = 0;
		} 

// extract parameters
    a= vhMdl[0],b=vhMdl[1],m=vhMdl[2],I_z=vhMdl[3];
    a0= F_ext[0],Crr=F_ext[1];
 	Bf= trMdl[0], Cf= trMdl[1], Df= trMdl[2], Ef= trMdl[3],Br= trMdl[4], Cr= trMdl[5], Dr= trMdl[6], Er= trMdl[7] ;
    g                       = 9.81;
    Fnr                     = m*g*b/(a+b);
    Fnf                     = m*g*a/(a+b)   ;     

//comptue the front/rear slip  [rad/s]
//ref: Hindiyeh Thesis, p58
    if (v_x >= 0.5)
        {
		a_F     = atan((v_y + a*r)/v_x) - d_f;
        a_R     = atan((v_y - b*r)/v_x);
		}
    else
        {
		a_F = 0;
        a_R = 0;

		}
//compute lateral tire force at the front
    TM_param_f[0]  = Bf;
	TM_param_f[1]  =  Cf;
	TM_param_f[2]  =  Df*Fnf;
	TM_param_f[3]  =  Ef;
    FyF         = TM_param_f[2]*sin(Cf*atan(TM_param_f[0]*a_F-TM_param_f[3]*(TM_param_f[0]*a_F-atan(TM_param_f[0]*a_F)))) ;
    FyF=FyF*-1;
//calculate FxR and limit it to tire friction circle
    FxR = (dvxdt+sign(v_x)*a0*v_x*v_x+(v_x!=0)*sign(v_x)*Crr*m*g-r*v_y)*m+FyF*sin(d_f);
    realFxR = max(min(FxR, Dr*Fnr), -Dr*Fnr);


    if (realFxR != FxR)
        {
		 ROS_INFO_STREAM("Can not support dvxdt, decrease maxDvxdt in vehicle class!");
		}


//compute lateral tire force at the rear
// ensure that magnitude of longitudinal/lateral force lie within friction circle
     TM_param_r[0]  = Br;
	TM_param_r[1]  =  Cr;
	TM_param_r[2]  =  Dr*Fnr;
	TM_param_r[3]  =  Er;
    FyR_paj         = -TM_param_r[2]*sin(Cr*atan(TM_param_r[0]*a_R-TM_param_r[3]*(TM_param_r[0]*a_R-atan(TM_param_r[0]*a_R)))) ;
    FyR_max     = sqrt(abs(Dr*Fnr*Dr*Fnr-FxR*FxR));
    Fy[0]          =FyR_max;
	Fy[1]=FyR_paj;
    if (abs(Fy[0])<abs(Fy[1]))
     	idx         =0;
    else   idx=1;
    FyR         = Fy[idx];
    
//compute next state
    nextstate[0]     = X + dt*(v_x*cos(phi) - v_y*sin(phi)) ;
    nextstate[1]      = Y + dt*(v_x*sin(phi) + v_y*cos(phi)) ;
    nextstate[2]    = phi + dt*r;
    nextstate[3]       = -r*v_x + 1/m*(FyF*cos(d_f) + FyR + F_side*cos(phi));
    nextstate[4]        = 1/I_z*(a*FyF*cos(d_f) - b*FyR);
    nextstate[5]    = v_y + dt * dvydt;
    nextstate[6]      = r   + dt * drdt;

    return ;
}



int main(int argc, char **argv)
{
  int i;
  ros::init(argc, argv, "sim");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("/vehicle/cmd_vel_stamped",1000,cmd_vel_stampedCallback); 
  ros::Subscriber sub2 = n.subscribe("/vehicle/steering_cmd",1000,steering_cmdCallback);
  ros::Publisher pub1 = n.advertise<dbw_mkz_msgs::SteeringReport>("/vehicle/steering_report",1000); 
  ros::Publisher pub2 = n.advertise<path_follower::state_Dynamic>("state_estimate",1000);
  ros::Rate loop_rate(50);
  ROS_INFO_STREAM("simulator node starts");


  dt=0.02;
  vhMdl[0]=1.2;
  vhMdl[1]=1.65;
  vhMdl[2]=1800;
  vhMdl[3]=3670;
  trMdl[0]=10.0;
  trMdl[1]=1.9;
  trMdl[2]=1.0;
  trMdl[3]=0.97;
  a0 = 0.0;
  Crr= 0.0;
  F_ext[0]=a0;
  F_ext[1]=Crr;
  maxSteeringRate = 850/180*pi;
  maxSteering = 525.0/180*pi;
  steeringRatio = 16 ;
  F_side=0;

  while(ros::ok())
  {
    ros::spinOnce();
    memset(nextstate, 0, 7 * sizeof(float));
    action[0] = max(min(action[0], 1.0f), -1.0f);
    action[1] = max(min(action[1], 1.0f), -1.0f);
    dvxdt = maxDvxdt * action[0];
    steering = action[1]*maxSteeringRate*dt + state[6]*steeringRatio;
    nextstate[6] = max(min(steering,maxSteering),-maxSteering)/steeringRatio;
    u[0] =nextstate[6];
    u[1]=dvxdt;
    f_6s();
    steeringreport.steering_wheel_angle=nextstate[6];   
    statedynamic.vx=nextstate[3];
    statedynamic.vy=nextstate[4];
    statedynamic.X=nextstate[0];
    statedynamic.Y=nextstate[1];
    statedynamic.psi=nextstate[2];
    statedynamic.wz=nextstate[5];
    pub1.publish(steeringreport);   
    pub2.publish(statedynamic);            
    ROS_INFO_STREAM("publish new state");
    for (i=0;i++;i<=6)
  	 state[i]=nextstate[i];
	}
  return 0;
}
