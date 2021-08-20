clear
clc

syms t0;
syms t1;
Function = @(x)80*exp(-0.2*t0);
i = int(Function,t0,0,t1);
time = solve(i == 200);

t1 = 15;
water = 400- int(Function,t0,0,t1);

fprintf('time=%f\n',time)
fprintf('water=%f\n',water)
