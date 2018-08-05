/********************************************************
  Autonomous Driving Software
  Copyright (c) 2017 MSC Lab, UC Berkeley 
  All rights reserved.

 ********************************************************/

#define _GLIBCXX_USE_C99_MATH 1
#define _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC 1
#include <cmath>
#include "path_follower/Vehicle.h"

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

namespace vlr {

    vehicle_state::vehicle_state() : added_error_x(0), added_error_y(0) {}

    void vehicle_state::set_mkz_params() {
        param.a = 1.20;                          //m
        param.b = 1.65;                          //m
        param.ftire_stiffness = 140000.0;        //N/rad
        param.rtire_stiffness = 120000.0;        //N/rad
        param.mass = 1800.0;                     //kg
        param.iz = 3270.0;                       //kg*m^2
        param.tau = 0.2;
        param.steering_ratio = MKZ_STEERING_RATIO; //16:1
        param.wheel_base = MKZ_WHEEL_BASE;         //
        
        param.imu_to_cg_dist = 0.5; //??MKZ_WHEEL_BASE + DGC_PASSAT_FA_TO_BUMPER_DIST - DGC_PASSAT_LENGTH / 2.0;
        param.torque_mode = 0;
        param.max_steering_rate = 650;
        param.max_steering = 525.0;
        
        param.max_wheel_angle = param.max_steering*(M_PI/180)/param.steering_ratio;
        param.max_wheel_rate = param.max_steering_rate*(M_PI/180)/param.steering_ratio;
        
      /*  
        param.max_torque = 1.0;
        param.max_brake = 100.0;
        param.max_throttle = 1.0;
        param.steer_inertia = 0.1;
        param.brake_decel_coef = 0.08125;        
        param.throttle_accel_coef = 3.0; 
      */          
    }

} // namespace vlr