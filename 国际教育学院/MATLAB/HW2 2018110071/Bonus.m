clear
clc
clc
format compact

Function = @(x)x^2*cos(2*pi*x);
[x0,y0] = fminbnd(Function,0,1)
fplot(Function,[-1 1])
hold on
plot(x0,y0,'o')
plot(-x0,y0,'o')