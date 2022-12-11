%% Problem 1
x = zeros(31);
for n=-15:15
    if n>=-4 && n<=4
        x(n+16) = 3*n;
    end
end
stem([-15:15],x);
xlabel('x');
ylabel('x(n)');
title('离散时间信号')
grid on;

%% Problem 2
%% 2-1
n = [0:32];
xn = exp(pi*n/8*1i);

subplot(2,2,1);
stem(n, real(xn));
xlabel('n');
ylabel('real(x(n))');
title('实部');
grid on;

subplot(2,2,2);
stem(n, imag(xn));
xlabel('n');
ylabel('imag(x(n))');
title('虚部');
grid on;

subplot(2,2,3);
stem(n, abs(xn));
xlabel('n');
ylabel('abs(x(n))');
title('幅值');
grid on;

subplot(2,2,4);
stem(n, angle(xn));
xlabel('n');
ylabel('angle(x(n))');
title('相位');
grid on;

%% 2-2
n = [-10:10];
xn = exp((-0.1+0.3j)*n);

subplot(2,2,1);
stem(n, real(xn));
xlabel('n');
ylabel('real(x(n))');
title('实部');
grid on;

subplot(2,2,2);
stem(n, imag(xn));
xlabel('n');
ylabel('imag(x(n))');
title('虚部');
grid on;

subplot(2,2,3);
stem(n, abs(xn));
xlabel('n');
ylabel('abs(x(n))');
title('幅值');
grid on;

subplot(2,2,4);
stem(n, angle(xn));
xlabel('n');
ylabel('angle(x(n))');
title('相位');
grid on;


%% Problem 3
xn = zeros(1, 5);
xn(1) = 2;
xn(3) = 1;
xn(4) = -1;
xn(5) = 3;


subplot(1,3,1);
stem([-5:5], [0 0 0 0 0 xn 0]);
xlabel('n');
ylabel('x(n)');
title('x(n)');
grid on;

subplot(1,3,2);
stem([-2:8], [0 0 0 0 0 xn 0]);
xlabel('n');
ylabel('x(n-3)');
title('x(n-3)');
grid on;

subplot(1,3,3);
stem([-5:5],[0 3 -1 1 0 2 0 0 0 0 0 ]);
xlabel('n');
ylabel('x(-n)');
title('x(-n)');
grid on;

%% Problem 4
xn = [1, 2, 3, 4];
yn = [1, 1, 1, 1, 1];

z = conv(xn, yn);
stem([0:7], z);
xlabel('n');
ylabel('z(n)');
title('z(n)');
grid on;

%% Problem 5
y = [1 4 2 1];
x = 1;
hn = impz(x, y, [0:12]);
for i=1:13
    hk(i) = hn(i);
end
stem([0:14], [hk 0 0]);
xlabel('n');
ylabel('h(n)');
grid on;

%% Problem 6
%% 6-1
close all; clear; clc;
syms k z
f = cos(k)*heaviside(k);
Fz = ztrans(f);
%% 6-2
Xz = 1 / ((1+z)*(2+z));
fk = iztrans(Xz, k);


%% Problem 7
b = [2 1];
a = [1 2 1];

% zplane(b, a);
% title('零极点图');
% figure(1)
% num = [0 2 1];
% den = [1 2 1];
% hn = impz(num, den);
% stem(hn, '.');
% xlabel('n');
% ylabel('h(n)');
% title('h(n)');

% figure(2)
[H, w] = freqz(num, den);
plot(w/pi, abs(H));
xlabel('w');
ylabel('abs(H)');
title('频率响应');
