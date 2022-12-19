%% Problem 1
num  = [0,0,6, 18];
den = [1, 8, 17, 10];
[z, p, k] = tf2zp(num, den);
[A, B, C, D] = tf2ss(num, den);
ZPK = zpk(z,p,k);
G = tf(num, den);
roots(G.den{1});
ABCD = ss(A,B,C,D);
%% Problem 2
A1= [-2.8 -1.4    0      0;
           1.4     0       0      0;
        - 1.8  -0.3 -1.4 -0.6;
            0        0      0.6   0];
        
B1 = [1; 0; 1; 0];
C1 = [0 0 0 1];
D1 = 0;
[num1, den1] = ss2tf(A1, B1, C1, D1);
[z1, p1, k1] = ss2zp(A1, B1, C1, D1);
G1 = tf(num1, den1);
ZPK1=zpk(z1,p1,k1);
roots(G1.den{1});
ABCD1 = ss(A1,B1,C1,D1);
