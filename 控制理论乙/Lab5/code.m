den = conv([1 4 3], [1 4 3]);
num = 55*[1 2];

% rlocus(num, dem);
[k, r] = rlocfind(num, dem); 

% w=3.15

[A, B, C, D] = tf2ss(num, den);
sys = ss(A,B,C,D);
sys_feedback = feedback(sys, 1);
t = 0:0.02:20;
y = step(sys_feedback, t);
plot(t, y);
title('闭环系统单位阶跃响应','fontsize',30,'fontweight','bold');
xlabel('t/s','fontsize',20,'fontweight','bold');
ylabel('U/V','fontsize',20,'fontweight','bold');
set(gca,'FontSize',20); 
grid minor
box off
set(gca,'color','non');