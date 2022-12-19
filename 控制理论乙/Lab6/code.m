%% Problem 1
num = [50];
den = conv(conv([1 1],[1 5]),[1 -2]);
% bode(num, den);
% margin(num ,den);
grid
[A, B, C, D] = tf2ss(num, den);
sys = ss(A,B,C,D);
sys_feedback = feedback(sys,1);
t=0:0.1:10;
y=impulse(sys_feedback, t);
plot(t, y);
title('闭环系统单位冲激响应','fontweight','bold');
xlabel('t/s','fontsize',10,'fontweight','bold');
ylabel('U/V','fontsize',10,'fontweight','bold');
set(gca,'FontSize',20); 

%% Problem 2
num = [16.7 0];
den = conv(conv([0.85 1],[0.25 1]),[0.0625 1]);
sys = tf(num,den);
sys_feedback=feedback(sys,1);
t=0:0.02:20;
sys_feedback = sys_feedback*10;
nyquist(sys_feedback);
% nyquist(num, den);
grid;

