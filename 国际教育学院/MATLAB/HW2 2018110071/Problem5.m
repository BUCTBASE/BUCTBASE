clear all;
clc;

Function=@(x)3*x(1)^4-2*x(1)^2+4*x(1)+1+x(2)^2-x(2);
[x1,min]=fminsearch(Function,[-5,-5])
x1=-1:0.01:-0.5;
range_x2=0:0.01:1;
[x1,x2]=meshgrid(x1,range_x2);
Y = 3*x1.^4-2*x1.^2+4*x1+1+x2.^2-x2;
mesh(x1,x2,Y)
