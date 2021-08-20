clear
clc

Function = @(x)(1000*9.8*(4/3*pi*1^3-pi*x^2/3*(3*1-x)))-(4/3*pi*1^3*800*9.8);
height = fzero(Function,[0,2])
fplot(Function) 
hold on
plot(height,Function(height),'o','MarkerSize',8)
