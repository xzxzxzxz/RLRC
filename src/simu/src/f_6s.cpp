


#include "f_6s.h"
#include<cmath>
#include <ros/ros.h>
using namespace std;

double signn(double k){

	if (k<0) return -1;

	if (k>0) return 1;

	return 0;

}

double *f_6s(double z[],double u[],double vhMdl[],double trMdl[],double F_ext[],double F_side,double dt){

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

    double X     = z[0];                                                         

    double Y     = z[1];                                                            

    double phi   = z[2];                                                     

    double v_x   = z[3];                                                    

    double v_y   = z[4];

    double r     = z[5];

    double d_f   = u[0];

    double dvxdt = u[1];
    

//prevent negative longitudinal speed

    double v_x_next =v_x +dt*dvxdt;

    if (v_x_next < 0)

       {

	   dvxdt = - v_x / dt;

        v_x_next = 0;

		} 



// extract parameters

    double a=vhMdl[0];
    double b=vhMdl[1];
    double m=vhMdl[2];
    double I_z=vhMdl[3];

    double a0= F_ext[0];
    double Crr=F_ext[1];

    double Bf= trMdl[0];
    double Cf= trMdl[1];
    double Df= trMdl[2];
    double Ef= trMdl[3];
    double Br= trMdl[4];
    double Cr= trMdl[5];
    double Dr= trMdl[6];
    double Er= trMdl[7] ;

    double g                       = 9.81;

    double Fnr                     = m*g*b/(a+b);

    double Fnf                     = m*g*a/(a+b)   ;     


//ref: Hindiyeh Thesis, p58
    double a_F,a_R;
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
    double TM_param_f[4];
    TM_param_f[0]  =  Bf;

    TM_param_f[1]  =  Cf;

    TM_param_f[2]  =  Df*Fnf;

    TM_param_f[3]  =  Ef;

    double FyF     = -TM_param_f[2]*sin(Cf*atan(TM_param_f[0]*a_F-TM_param_f[3]*(TM_param_f[0]*a_F-atan(TM_param_f[0]*a_F)))) ;

//calculate FxR and limit it to tire friction circle

    double FxR = (dvxdt+signn(v_x)*a0*v_x*v_x+(v_x!=0)*signn(v_x)*Crr*m*g-r*v_y)*m+FyF*sin(d_f);

    double realFxR = max(min(FxR, Dr*Fnr), -Dr*Fnr);


    if (realFxR != FxR)

        {

		 ROS_INFO_STREAM("Can not support dvxdt, decrease maxDvxdt in vehicle class!");

		}



// ensure that magnitude of longitudinal/lateral force lie within friction circle
    double TM_param_r[4];
    TM_param_r[0]  =  Br;

    TM_param_r[1]  =  Cr;

    TM_param_r[2]  =  Dr*Fnr;

    TM_param_r[3]  =  Er;

    double FyR_paj  = -TM_param_r[2]*sin(Cr*atan(TM_param_r[0]*a_R-TM_param_r[3]*(TM_param_r[0]*a_R-atan(TM_param_r[0]*a_R)))) ;

    double FyR_max  = sqrt(abs(Dr*Fnr*Dr*Fnr-FxR*FxR)); 
    
    double Fy[2];

    Fy[0]          = FyR_max;

    Fy[1]          = FyR_paj;
	
    int idx;

    if (abs(Fy[0])<abs(Fy[1]))

     	 idx       =0;

    else   idx=1;

    double FyR         = Fy[idx];

   
//compute next state
    static double znext[6];
    znext[0]        = X + dt*(v_x*cos(phi) - v_y*sin(phi)) ;

    znext[1]        = Y + dt*(v_x*sin(phi) + v_y*cos(phi)) ;

    znext[2]        = phi + dt*r;

    znext[3]        = v_x_next;
  
    znext[4]        = v_y + dt *(-r*v_x + 1/m*(FyF*cos(d_f) + FyR + F_side*cos(phi)));

    znext[5]        = r   + dt * 1/I_z*(a*FyF*cos(d_f) - b*FyR);

    return znext;

}

