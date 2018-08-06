


#include "f_6s.h"
#include<cmath>
#include <ros/ros.h>
using namespace std;

float signn(float k){

	if (k<0) return -1;

	if (k>0) return 1;

	return 0;

}

float *f_6s(float z[],float u[],float vhMdl[],float trMdl[],float F_ext[],float F_side,float dt){

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

    float X     = z[0];                                                         

    float Y     = z[1];                                                            

    float phi   = z[2];                                                     

    float v_x   = z[3];                                                    

    float v_y   = z[4];

    float r     = z[5];

    float d_f   = u[0];

    float dvxdt = u[1];


//prevent negative longitudinal speed

    float v_x_next =v_x +dt*dvxdt;

    if (v_x_next < 0)

       {

	   dvxdt = - v_x / dt;

        v_x_next = 0;

		} 



// extract parameters

    float a=vhMdl[0];
    float b=vhMdl[1];
    float m=vhMdl[2];
    float I_z=vhMdl[3];

    float a0= F_ext[0];
    float Crr=F_ext[1];

    float Bf= trMdl[0];
    float Cf= trMdl[1];
    float Df= trMdl[2];
    float Ef= trMdl[3];
    float Br= trMdl[4];
    float Cr= trMdl[5];
    float Dr= trMdl[6];
    float Er= trMdl[7] ;

    float g                       = 9.81;

    float Fnr                     = m*g*b/(a+b);

    float Fnf                     = m*g*a/(a+b)   ;     


//ref: Hindiyeh Thesis, p58
    float a_F,a_R;
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
    float TM_param_f[4];
    TM_param_f[0]  =  Bf;

    TM_param_f[1]  =  Cf;

    TM_param_f[2]  =  Df*Fnf;

	TM_param_f[3]  =  Ef;

    float FyF         = TM_param_f[2]*sin(Cf*atan(TM_param_f[0]*a_F-TM_param_f[3]*(TM_param_f[0]*a_F-atan(TM_param_f[0]*a_F)))) ;

    FyF=FyF*-1;

//calculate FxR and limit it to tire friction circle

    float FxR = (dvxdt+signn(v_x)*a0*v_x*v_x+(v_x!=0)*signn(v_x)*Crr*m*g-r*v_y)*m+FyF*sin(d_f);

    float realFxR = max(min(FxR, Dr*Fnr), -Dr*Fnr);


    if (realFxR != FxR)

        {

		 ROS_INFO_STREAM("Can not support dvxdt, decrease maxDvxdt in vehicle class!");

		}



// ensure that magnitude of longitudinal/lateral force lie within friction circle
    float TM_param_r[4];
    TM_param_r[0]  = Br;

    TM_param_r[1]  =  Cr;

    TM_param_r[2]  =  Dr*Fnr;

    TM_param_r[3]  =  Er;

    float FyR_paj  = -TM_param_r[2]*sin(Cr*atan(TM_param_r[0]*a_R-TM_param_r[3]*(TM_param_r[0]*a_R-atan(TM_param_r[0]*a_R)))) ;

    float FyR_max  = sqrt(abs(Dr*Fnr*Dr*Fnr-FxR*FxR));
    
    float Fy[2];

    Fy[0]          = FyR_max;

    Fy[1]          = FyR_paj;
	
    int idx;

    if (abs(Fy[0])<abs(Fy[1]))

     	 idx       =0;

    else   idx=1;

    float FyR         = Fy[idx];

   
//compute next state
    static float znext[7];
    
    znext[0]        = X + dt*(v_x*cos(phi) - v_y*sin(phi)) ;

    znext[1]        = Y + dt*(v_x*sin(phi) + v_y*cos(phi)) ;

    znext[2]        = phi + dt*r;

    znext[3]        = -r*v_x + 1/m*(FyF*cos(d_f) + FyR + F_side*cos(phi));

    znext[4]        = 1/I_z*(a*FyF*cos(d_f) - b*FyR);

    znext[5]        = v_y + dt * znext[3];

    znext[6]        = r   + dt * znext[4];
    
    return znext;

}

