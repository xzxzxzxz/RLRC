%% DOB Implementation 
%  Setting encoding
clear
%clc

%% Vehicle Model (Linear Bicycle model)
% Parameters
a = 1.20;
b = 1.65;
m = 1800.0;
Iz = 3270.0;
BCD = 19.0;
g = 9.81;
Fnf = m * g * b/(a+b);
Fnr = m * g * a/(a+b);
Caf = BCD * Fnf;
Car = BCD * Fnr;
dt = 0.02;
dt_ros_single = single(0.02);
dt_ros = 0.02;
v = 10;
kappa = 0;
dphi = 0;
ds = 5;
dy = 0;
steering_ratio = 14.8;

kc11 = single(1);
kc12 = single(0.02);
% Discrete time ss (output: beta_s & dphidt)
a1f = @(v, dphi, dy, kappa) [kappa*sin(dphi)/(1-kappa*dy), -kappa^2*v*cos(dphi)/(1-kappa*dy)^2, kappa*sin(dphi)/(1-kappa*dy), 1+kappa*ds*sin(dphi)/(1-kappa*dy)];
a2f = @(v, dphi, dy, kappa) [v*cos(dphi), 0, cos(dphi), ds*cos(dphi)]; 
a3f = @(v, dphi, dy, kappa) [0, 0, -(Caf+Car)/(m*v), -v-(Caf*a-Car*b)/(m*v)];
a4f = @(v, dphi, dy, kappa) [0, 0,  -(a*Caf-b*Car)/(Iz*v), -(Caf*a^2+Car*b^2)/(Iz*v)];
b3f = Caf / m;
b4f = a * Caf / Iz;
A = @(v, dphi, dy, kappa) [a1f(v, dphi, dy, kappa); a2f(v, dphi, dy, kappa); a3f(v, dphi, dy, kappa); a4f(v, dphi, dy, kappa)];
B = [0; 0; b3f; b4f];
C1 = @(v, dphi, dy, kappa) [kc11 kc12 1/v ds/v];
C2 = @(v, dphi, dy, kappa) [1 0 1/v ds/v; 0 1 0 0];

% Discrete time tf
sys = ss(A(v, dphi, dy, kappa), B, C1(v, dphi, dy, kappa), zeros(1, 1));
sysd = c2d(sys, dt);
%sysd = sys;
[bp, ap] = ss2tf(sysd.A, sysd.B, sysd.C, sysd.D);
pnu = bp;
pde = ap;
Gop = tf(pnu, pde, 'Ts', dt, 'Variable', 'z');
Gde = tf(1, [1,0], 'Ts', dt, 'Variable', 'z');
Gop = Gop * Gde;

kc2 = single(0.5);
%rlocus(Gop);

%% Design DOB
% inverse Gop in realizable form 
[Numc, Denc] = tfdata(Gop);
Dn = single(Denc{1}/Numc{1}(3));
Dd = single([Numc{1}(3:end) 0 0]/Numc{1}(3));
D = tf(Dn, Dd, 'Ts', dt, 'Variable', 'z');
N = tf([0 0 1], 1, 'Ts', dt, 'Variable', 'z^-1');

% design Q filter
wn = 5;
eps = 0.8;
%Q = tf(wn^2, [1 2*eps*wn wn^2],'Variable','s');
%Q = c2d(Q, dt, 'zoh');
Q = tf(0.08,[1 -1 0.08],dt,'Variable','z^-1');
[NQ, DQ] = tfdata(Q);
NQ{1} = single(NQ{1});
DQ{1} = single(DQ{1});

%% Lookup Table
v_list = 1:0.2:20;
dphi_list = -1:0.1:1;
kappa_list = -0.02:0.005:0.02;
dy_list = -4:0.5:4;

%v_list = [10, 10.1];
%dphi_list = [0, 0.0001];

init = single(zeros(length(v_list), length(dphi_list), length(kappa_list), length(dy_list)));
a1 = init;
a2 = init;
a3 = init;
b0 = init;
b1 = init;
b2 = init;
b3 = init;
b4 = init;
b5 = init;

for i=1:length(v_list)
    for j=1:length(dphi_list)
        for k=1:length(kappa_list)
            for p=1:length(dy_list)
                disp([i,j,k,p])
                v = v_list(i);
                dphi = dphi_list(j);
                kappa = kappa_list(k);
                dy = dy_list(p);
                sys = ss(A(v, dphi, dy, kappa), B, C1(v, dphi, dy, kappa), zeros(1,1));
                sysd = c2d(sys, dt);
                [pnu, pde] = ss2tf(sysd.A, sysd.B, sysd.C, sysd.D); 
                Gop = tf(pnu, pde, 'Ts', dt, 'Variable', 'z');
                Gop = Gop * Gde;
                [Numc, Denc] = tfdata(Gop);
                Dnk = single(Denc{1}/Numc{1}(3));
                Ddk = single([Numc{1}(3:end) 0 0]/Numc{1}(3));
                b0(i,j,k,p) = Dnk(1);
                b1(i,j,k,p) = Dnk(2);
                b2(i,j,k,p) = Dnk(3);
                b3(i,j,k,p) = Dnk(4);
                b4(i,j,k,p) = Dnk(5);
                b5(i,j,k,p) = Dnk(6);
                a1(i,j,k,p) = Ddk(2);
                a2(i,j,k,p) = Ddk(3);
                a3(i,j,k,p) = Ddk(4);
            end
        end
    end
end
%         
