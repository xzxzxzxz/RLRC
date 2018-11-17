%% DOB Implementation 
%  Setting encoding
clear
clc

%% Vehicle Model (Linear Bicycle model)
% Parameters
a = 1.20;
b = 1.65;
m = 1800.0;
Iz = 3270.0;
BCD = 19.0;
g = 9.81;
Fnf = m * g * a/(a+b);
Fnr = m * g * b/(a+b);
Caf = BCD * Fnf;
Car = BCD * Fnr;
dt = 0.02;
dt_ros_single = single(0.02);
dt_ros = 0.02;
vx = 10;
ds = 10;
steering_ratio = 14.8;

% Discrete time ss (output: beta_s & dphidt)
a11 = @(vx) - (Caf + Car) / (m * vx);
a12 = @(vx) - vx - (Caf * a - Car * b) / (m * vx);
a21 = @(vx) - (a * Caf - b * Car) / (Iz * vx);
a22 = @(vx) - (Caf * a^2 + Car * b^2) / (Iz *vx);
b1 = Caf / m;
b2 = a * Caf / Iz;
A = @(vx) [a11(vx) 0 a12(vx); 0 0 1; a21(vx) 0 a22(vx)] * dt + eye(3);
B = [b1; 0; b2] * dt;
C = @(vx) [1/vx 0 ds/vx; 0 0 1];

% Discrete time tf
[bp, ap] = ss2tf(A(vx), B, C(vx), zeros(2,1));
pnu = {bp(1,:); bp(2,:)};
pde = {ap; ap};
Gptf = tf(pnu, pde, 'Ts', dt, 'Variable', 'z');

% over-all open loop system 
Gi = tf(dt, [1,-1], 'Ts', dt, 'Variable', 'z');
Ceq = @(vx) [1/vx 1 ds/vx];
Gde = tf(1, [1,0], 'Ts', dt, 'Variable', 'z');
[bpeq, apeq] = ss2tf(A(vx), B, Ceq(vx), zeros(1,1));
Gop = tf(bpeq, apeq, 'Ts', dt, 'Variable', 'z');
Gop = Gop * Gde;

kc1 = single(0.4);
kc2 = single(0.06);
Gc1 = kc1 + vx*Gi;
Gc2 = kc2;
Gop = Gop * Gc1;

rlocus(Gop);
%% Controller Configuration
% dsigmadt = k1 * delta_phi + k2 * delta_y
k1 = kc1 * kc2;
k2 = kc2;

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
Q = tf(0.01,[1 -1 0.01],dt,'Variable','z^-1');
[NQ, DQ] = tfdata(Q);
NQ{1} = single(NQ{1});
DQ{1} = single(DQ{1});
