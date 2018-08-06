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


float  errorbound,state[7]={0},nextstate[7]={0},action[2],dt,maxSteeringRate,maxDvxdt,steering,steeringRatio,maxSteering,pi=3.1415926,dvxdt;


float sign(float k){

	if (k<0) return -1;

	if (k>0) return 1;

	return 0;

}

void errorcallback(simu::DynamicParamConfig &config, uint32_t level) {
  ROS_INFO_STREAM("Reconfigure" );
  errorbound=config.errorbound;
               
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

int main(int argc, char **argv)

{
  
  int i;

  ros::init(argc, argv, "sim");

  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("/vehicle/cmd_vel_stamped",10,cmd_vel_stampedCallback); 

  ros::Subscriber sub2 = n.subscribe("/vehicle/steering_cmd",10,steering_cmdCallback);

  ros::Publisher pub1 = n.advertise<dbw_mkz_msgs::SteeringReport>("/vehicle/steering_report",10); 

  ros::Publisher pub2 = n.advertise<path_follower::state_Dynamic>("state_estimate",10);
  
  dynamic_reconfigure::Server<simu::DynamicParamConfig> server;
  dynamic_reconfigure::Server<simu::DynamicParamConfig>::CallbackType f;
  
   f = boost::bind(&errorcallback, _1, _2);
  server.setCallback(f);
  
  ros::spinOnce();
  
  ros::Rate loop_rate(50);

  ROS_INFO_STREAM("simulator node starts");
  
  
  dt=0.02;
  float rannum[17];
  srand( (unsigned)time( NULL ) );
  
  for(i=0;i<14;i++)
    
     rannum[i]=rand()/(float)(RAND_MAX/2)-1;
  float vhMdl[4],trMdl[8],a0,Crr,F_ext[2];

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

    memset(nextstate, 0, 7 * sizeof(float));

    action[0] = max(min(action[0], 1.0f), -1.0f);

    action[1] = max(min(action[1], 1.0f), -1.0f);

    dvxdt = maxDvxdt * action[0];

    steering = action[1]*maxSteeringRate*dt + state[6]*steeringRatio;

    nextstate[6] = max(min(steering,maxSteering),-maxSteering)/steeringRatio;
    
    float u[2],z[6];
    
    u[0]=nextstate[6];

    u[1]=dvxdt;
    
    for(i=0;i<=5;i++)
      z[0]=state[0];
    float F_side=0;
    float *ptr;
    ptr=f_6s(z,u,vhMdl,trMdl,F_ext,F_side,dt);
    for(i=0;i<=5;i++)
       nextstate[i]=*(ptr+i);
       
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



