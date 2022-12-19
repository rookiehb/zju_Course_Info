%% problem 1
A = [-0.5572 -0.7814;
        0.7814  0];
B = [1; 0];
C = [1.9691 6.4493];
D = 0;

t= 0:0.5:50;
sys = ss(A, B, C, D);

% 单位阶跃响应
y = step(sys,t);
% plot(t, y);

% 冲击响应函数
y1 = impulse(sys, t);
% plot(t, y1);

% x=[1 0] 零输入响应
x0 = [1 0];
y2 = initial(sys, x0, t);
% plot(t, y2);

% 初始mmm态为零，系统斜坡输入响应
x = t;
y3 = lsim(sys, x, t);
plot(t, y3);

%% problem 2
w = 1;
zeta = 2;
num = [w^2];
den = [1 2*zeta*w w^2];
[A1, B1, C1, D1] = tf2ss(num, den);
sys = ss(A1,B1,C1,D1);

t = 0:0.1:20;
y4 = step(sys, t);
plot(t, y4);

%% problem 3
num1 = [5 25 30];
den1 = [1 6 10 8];

[A2, B2, C2, D2] = tf2ss(num1, den1);
sys = ss(A2,B2,C2,D2);
t = 0:0.1:20;

% 单位阶跃
y_step = step(sys, t);
% 单位脉冲
y_impulse = impulse(sys, t);
% 零输入响应
x0 = [1;1;-1];
y_zeroInput = initial(sys, x0, t);

% plot(t, y_step+y_zeroInput);
plot(t, y_impulse+y_zeroInput);