/********************************************************
  Autonomous Driving Software
  Copyright (c) 2018 MSC Lab, UC Berkeley 
  All rights reserved.
 ********************************************************/

// ROS Includes
#include <ros/ros.h>
// User defined includes
#include "dbw_mkz_msgs/SteeringReport.h"
#include "dbw_mkz_msgs/SteeringCmd.h"
#include "path_follower/state_Dynamic.h"
#include "geometry_msgs/TwistStamped.h"
#include <dynamic_reconfigure/server.h>
#include <simu/DynamicParamConfig.h>
#include "f_6s.h"
// cpp includes
#include <cmath>
#include<iostream>
#include<algorithm>
#include<time.h>
using namespace std;
//To do: define global variable 
dbw_mkz_msgs::SteeringReport steeringreport;
dbw_mkz_msgs::SteeringCmd steeringcmd;
path_follower::state_Dynamic statedynamic;
geometry_msgs::TwistStamped twistcmd;
double  errorbound=0,state[7]={0},nextstate[7]={0},action[2]={0},dt,maxSteeringRate,maxDvxdt,steering,steeringRatio,maxSteering,pi=3.1415926,dvxdt,init_flag=0,start_flag=0;

double signnn(double k){

	if (k<0) return -1;

	if (k>0) return 1;

	return 0;

}

void errorcallback(simu::DynamicParamConfig &config, uint32_t level) {
    ROS_INFO_STREAM("Reconfigure");
    start_flag=config.Run;   
    if (init_flag==0 && start_flag==1)
	  {
	  errorbound=config.errorbound;
	  state[0]=config.X_init;
	  state[1]=config.Y_init;
	  state[2]=config.phi_init;
	  state[3]=config.vx_init;
	  state[6]=config.steering_init/16;
	  init_flag=1;  
          ROS_INFO_STREAM("Run" );
         }   
    
}

void cmd_vel_stampedCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)

{
   action[0]=(msg->twist.linear.x-state[3])/dt/maxDvxdt;
  
}


void steering_cmdCallback(const dbw_mkz_msgs::SteeringCmd::ConstPtr& msg)

{
   double steering_rate,steering_cmd;
   steering_cmd = msg->steering_wheel_angle_cmd;
   steering_rate = msg->steering_wheel_angle_velocity;
   ROS_INFO_STREAM("steering_cmd"<<steering_cmd);
   ROS_INFO_STREAM("steering_rate"<<steering_rate);
   if (steering_rate==0) steering_rate=maxSteeringRate;
   action[1] = min(abs(steering_rate/maxSteeringRate),abs(state[6]*steeringRatio-steering_cmd)/dt/maxSteeringRate);
   action[1]=action[1]*signnn(steering_cmd-state[6]*steeringRatio); 
   
}

int main(int argc, char **argv)

{
  
  int i;
  ros::init(argc, argv, "sim");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("/vehicle/cmd_vel_stamped",1,cmd_vel_stampedCallback); 
  ros::Subscriber sub2 = n.subscribe("/vehicle/steering_cmd",1,steering_cmdCallback);
  ros::Publisher pub1 = n.advertise<dbw_mkz_msgs::SteeringReport>("/vehicle/steering_report",1); 
  ros::Publisher pub2 = n.advertise<path_follower::state_Dynamic>("state_estimate",1);
  dynamic_reconfigure::Server<simu::DynamicParamConfig> server;
  dynamic_reconfigure::Server<simu::DynamicParamConfig>::CallbackType f;
  f = boost::bind(&errorcallback, _1, _2);
  server.setCallback(f);
  dt=0.02;
  ros::Rate loop_rate(1/dt);
  ROS_INFO_STREAM("simulator node starts");
  double rannum[17];
  srand( (unsigned)time( NULL ) );
  for(i=0;i<14;i++)
     rannum[i]=rand()/(double)(RAND_MAX/2)-1;
  double vhMdl[4],trMdl[8],a0,Crr,F_ext[2];
  vhMdl[0]=1.2*(rannum[0] + 1);
  vhMdl[1]=1.65*(rannum[1] + 1);
  vhMdl[2]=1800*(rannum[2] + 1);
  vhMdl[3]=3270*(rannum[3] + 1);
  trMdl[0]=10.0*(rannum[4] + 1);
  trMdl[1]=1.9*(rannum[5] + 1);
  trMdl[2]=1.0*(rannum[6] + 1);
  trMdl[3]=0.97*(rannum[7] + 1);
  trMdl[4]=10.0*(rannum[8] + 1);
  trMdl[5]=1.9*(rannum[9] + 1);
  trMdl[6]=1.0*(rannum[10] + 1);
  trMdl[7]=0.97*(rannum[11] + 1);
  a0 = 0.0*(rannum[12] + 1);
  Crr= 0.0*(rannum[13] + 1);
  F_ext[0]=a0;
  F_ext[1]=Crr;
  maxSteeringRate = 650/180*pi;
  maxSteering = 525.0/180*pi;
  steeringRatio = 16 ;
  maxDvxdt = 5 ;
  while(ros::ok())
  {
    ros::spinOnce();
    if (init_flag*start_flag==0)
	{
	loop_rate.sleep();	
	continue;
	}
    memset(nextstate, 0, 7 * sizeof(double));
    action[0] = max(min(action[0], 1.0), -1.0);
    action[1] = max(min(action[1], 1.0), -1.0);
    dvxdt = maxDvxdt * action[0];
    steering = action[1]*maxSteeringRate*dt + state[6]*steeringRatio;
    nextstate[6] = max(min(steering,maxSteering),-maxSteering)/steeringRatio;
    double u[2],z[6];
    u[0]=nextstate[6];
    u[1]=dvxdt;
    for(i=0;i<=5;i++)
      z[i]=state[i];
    double F_side=0;
    double *ptr;
    ptr=f_6s(z,u,vhMdl,trMdl,F_ext,F_side,dt);
    for(i=0;i<=5;i++)
       nextstate[i]=*(ptr+i);
  /*  ROS_INFO_STREAM("X"<<state[0]);
    ROS_INFO_STREAM("Y"<<state[1]);
    ROS_INFO_STREAM("phi"<<state[2]);*/
    ROS_INFO_STREAM("v_x"<<state[3]);
    ROS_INFO_STREAM("v_y"<<state[4]);
    ROS_INFO_STREAM("r"<<state[5]);
    ROS_INFO_STREAM("d_f"<<state[6]);	
    ROS_INFO_STREAM("sterring"<<steering);
    steeringreport.steering_wheel_angle=nextstate[6]*steeringRatio;   
    statedynamic.vx=nextstate[3];
    statedynamic.vy=nextstate[4];
    statedynamic.X=nextstate[0];
    statedynamic.Y=nextstate[1];
    statedynamic.psi=nextstate[2];
    statedynamic.wz=nextstate[5];
    pub1.publish(steeringreport);   
    pub2.publish(statedynamic);            
    for (i=0;i<=6;i++)
  	 state[i]=nextstate[i];
    loop_rate.sleep();
	}
  return 0;

}

