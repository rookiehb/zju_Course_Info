%% Q1(1)
N1=11;
x1 = zeros(1,N1);
for i=1:N1
    x1(i)=(0.9*exp(1i*pi/3))^(i-1);
end
xk1 = zeros(1,N1);
for k=1:N1
    for n=1:N1
        xk1(k)  = xk1(k) + x1(n)*exp(-1i*2*pi/N1*(n-1)*(k-1) );
    end
end

subplot(1,2,1)
x=0:10;
stem(x,abs(xk1));
axis([0 10 0 8]);
xlabel('x');
ylabel('|X(K)|')
title('幅频特性')
grid on;

subplot(1,2,2);
stem(x,angle(xk1));
axis([0 10 -pi/2 pi/2]);
xlabel('x');
ylabel('angle(X(K))');
title('相频特性')
grid on;


%% Q1(2)
N2 = 21;
x2 = zeros(1,N2);
for i=-10:1:10
    x2(i+11)=2^i;
end
xk2 = zeros(1,N2);
for k=1:N2
    for n=1:N2
        xk2(k) = xk2(k) + x2(n)*exp(-1i*2*pi/N2*(n-1)*(k-1));
    end
end

subplot(1,2,1)
x=-10:10;
stem(x,abs(xk2));
axis([-10 10 0 2500]);
xlabel('x');
ylabel('|X(K)|')
title('幅频特性')
grid on;

subplot(1,2,2);
stem(x,angle(xk2));
axis([-10 10 -4 4]);
xlabel('x');
ylabel('angle(X(K))');
title('相频特性')
grid on;

%% Q2
close all; clear; clc;
a=[1.0, 0, 0.81];
b=[1.0, 0, -1.0];
% 
% disp('H(z)');
% printsys(b,a,'z')

N=32;
hn= impz(b,a,0:N-1);
gn = stepz(b,a,0:N-1);

figure(1)
subplot(1,2,1);
stem(0:N-1,hn);
title('单位脉冲响应');
ylabel('h(n)');
xlabel('n');
grid on;

subplot(1,2,2)
stem(0:N-1,gn);
title('单位阶跃响应');
ylabel('g(n)');
xlabel('n');
grid on;

figure(2);
NN=50;
[h, w] = freqz(b, a, 2001, 'whole');
Hh = 20*log10(abs(h));
Hw = angle(h)*180/pi;
subplot(1,2,1);
plot(w/pi, Hh);
xlabel('角频率(w)/rad');
ylabel('幅值/dB');
title('幅频特性');
grid on;

subplot(1,2,2);
stem(w/pi, Hw);
xlabel('角频率(w)/rad');
ylabel('相位');
title('相频特性');
grid on;

%% Q3
N = 51;
x = zeros(1,N);
for i=1:51
    x(i) = cos(0.82*pi*(i-1)) + 2*sin(pi*(i-1));
end
XK = zeros(1,N);
for k=1:N
    for n = 1:N
        XK(k) = XK(k) + x(n)*exp(-1i*2*pi/N*(n-1)*(k-1));
    end
end

figure(1);
subplot(1,2,1);
x=0:N-1;
stem(x,abs(XK));
axis([0 50 0 30]);
xlabel('x');
ylabel('|X(K)|')
title('幅频特性')
grid on;

subplot(1,2,2);
stem(x,angle(XK));
axis([0 50 -3 4]);
xlabel('x');
ylabel('angle(X(K))');
title('相频特性')
grid on;

%% Q4
% 进行DFT和FFT的比较

for m=2:1:4
    startTime=clock;
    N=4^m;
    n=[1:1:N];
    xn=sin(0.2*pi*n)+randn(1,N);
    XK = zeros(1,N);
    for y=1:1000
        for k = 1:N
            for n = 1:N
                XK(k) = XK(k) + xn(n)*exp(-1i*2*pi/N*(n-1)*(k-1));
            end
        end
   end
    endTime=clock;
    DFT_Time=etime(endTime,startTime);
    disp("m is "+m+" | 1000 times | DFT Time is " + DFT_Time);
    
    startTime1=clock;
   for y=1:1000
        XK2 = fft(xn);
   end
    endTime1=clock;
    FFT_Time=etime(endTime1,startTime1);
    disp("m is "+m+" | 1000 times | FFT Time is "  + FFT_Time);
end
%% Q5
L1 = 23;L2 = 16;
x1 = zeros(1,L1);x2 = zeros(1,L2);
h1 = zeros(1,L1);h2 = zeros(1,L2);

for i=1:16
    x1(i) = i-1;
    x2(i) = i-1;
end

for i=1:8
    h1(i) = 1;
    h2(i) = 1;
end

XK1 = fft(x1); HK1=fft(h1);
XK2 = fft(x2); HK2=fft(h2);

y1 = ifft(XK1.*HK1);
y2 = ifft(XK2.*HK2);

subplot(2,2,1);
stem(0:L1-1,abs(y1));
xlabel('k');
ylabel('|X(K)|');
title('线性卷积幅频特性');
grid on;

subplot(2,2,2);
stem(0:L1-1,angle(y1));
xlabel('k');
ylabel('angel|X(K)|')
title('线性卷积相频特性')
grid on;

subplot(2,2,3);
stem(0:L2-1,abs(y2));
xlabel('k');
ylabel('|X(K)|')
title('混叠结果幅频特性')
grid on;

subplot(2,2,4);
stem(0:L2-1,angle(y2));
xlabel('k');
ylabel('angel|X(K)|')
title('混叠结果相频特性')
grid on;

%% Q6
n=[0:1:32000];
xn = cos(pi*13/32*n) + cos(7*pi/16*n) + cos(9*pi/16*n);

XK1 = fft(xn(1:16),16);
figure(1);
subplot(1,2,1);
stem(0:15,abs(XK1));
xlabel('k');
ylabel('|X(K)|');
title('幅频特性');
grid on;

subplot(1,2,2);
stem(0:15,angle(XK1));
xlabel('k');
ylabel('angel|X(K)|');
title('相频特性');
grid on;


XK2 = fft(xn(1:16), 256);
figure(2);
subplot(1,2,1);
stem(0:255,abs(XK2));
xlabel('k');
ylabel('|X(K)|');
title('幅频特性');
grid on;

subplot(1,2,2);
stem(0:255,angle(XK2));
xlabel('k');
ylabel('angel|X(K)|');
title('相频特性');
grid on;


XK3 = fft(xn(1:256),  256);
figure(3);
subplot(1,2,1);
stem(0:255,abs(XK3));
xlabel('k');
ylabel('|X(K)|');
title('幅频特性');
grid on;

subplot(1,2,2);
stem(0:255,angle(XK3));
xlabel('k');
ylabel('angel|X(K)|');
title('相频特性');
grid on;
