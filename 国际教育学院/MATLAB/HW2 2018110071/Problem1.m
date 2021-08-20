clear all;
clc;

x1=fzero(@(x)4*x^3-3*x^2-30,[0,5])
x2=fzero(@(x)3*exp(2*x)-10,[0,1])
x3=fzero(@(x)5*(10^x)-10*x^2,[-1,1])