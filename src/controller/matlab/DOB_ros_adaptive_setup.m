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
vx = 10;
dphi = 0;
ds = 10;
steering_ratio = 14.8;

kc11 = single(0.3);
kc12 = single(1);
% Discrete time ss (output: beta_s & dphidt)
a1 = @(vx, dphi) [0, 0, 0, 1];
a2 = @(vx, dphi) [vx/cos(dphi)^2, 0, 1, ds]; 
d2 = @(vx, dphi) tan(dphi)-dphi/cos(dphi)^2*vx;
a3 = @(vx, dphi) [0, 0, -(Caf+Car)/(m*vx), -vx-(Caf*a-Car*b)/(m*vx)];
a4 = @(vx, dphi) [0, 0,  -(a*Caf-b*Car)/(Iz*vx), -(Caf*a^2+Car*b^2)/(Iz*vx)];
b3 = Caf / m;
b4 = a * Caf / Iz;
A = @(vx, dphi) [a1(vx, dphi); a2(vx, dphi); a3(vx, dphi); a4(vx, dphi)];
B = [0; 0; b3; b4];
C1 = @(vx, dphi) [kc11 kc12 1/vx ds/vx];
C2 = @(vx, dphi) [1 0 1/vx ds/vx; 0 1 0 0];

% Discrete time tf
sys = ss(A(vx, dphi), B, C1(vx, dphi), zeros(1,1));
sysd = c2d(sys, dt);
%sysd = sys;
[bp, ap] = ss2tf(sysd.A, sysd.B, sysd.C, sysd.D);
pnu = bp;
pde = ap;
Gop = tf(pnu, pde, 'Ts', dt, 'Variable', 'z');
Gde = tf(1, [1,0], 'Ts', dt, 'Variable', 'z');
Gop = Gop * Gde;

kc2 = single(0.1);
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
Q = tf(0.02,[1 -1 0.02],dt,'Variable','z^-1');
[NQ, DQ] = tfdata(Q);
NQ{1} = single(NQ{1});
DQ{1} = single(DQ{1});

%% Lookup Table
%vx_list = 1:0.1:20;
%dphi_list = -1:0.1:1;
vx_list = [10, 10.1];
dphi_list = [0, 0.0001];

a1 = zeros(length(vx_list), length(dphi_list));
a2 = zeros(length(vx_list), length(dphi_list));
a3 = zeros(length(vx_list), length(dphi_list));
b0 = zeros(length(vx_list), length(dphi_list));
b1 = zeros(length(vx_list), length(dphi_list));
b2 = zeros(length(vx_list), length(dphi_list));
b3 = zeros(length(vx_list), length(dphi_list));
b4 = zeros(length(vx_list), length(dphi_list));
b5 = zeros(length(vx_list), length(dphi_list));

for i=1:length(vx_list)
    for j=1:length(dphi_list)
        vx = vx_list(i);
        dphi = dphi_list(j);
        sys = ss(A(vx, dphi), B, C1(vx, dphi), zeros(1,1));
        sysd = c2d(sys, dt);
        [pnu, pde] = ss2tf(sysd.A, sysd.B, sysd.C, sysd.D); 
        Gop = tf(pnu, pde, 'Ts', dt, 'Variable', 'z');
        Gop = Gop * Gde;
        [Numc, Denc] = tfdata(Gop);
        Dnk = single(Denc{1}/Numc{1}(3));
        Ddk = single([Numc{1}(3:end) 0 0]/Numc{1}(3));
        b0(i,j) = Dnk(1);
        b1(i,j) = Dnk(2);
        b2(i,j) = Dnk(3);
        b3(i,j) = Dnk(4);
        b4(i,j) = Dnk(5);
        b5(i,j) = Dnk(6);
        a1(i,j) = Ddk(2);
        a2(i,j) = Ddk(3);
        a3(i,j) = Ddk(4);
    end
end
%         
