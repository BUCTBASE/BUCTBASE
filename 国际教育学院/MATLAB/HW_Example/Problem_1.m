clear all
close all
clc
format compact

MyFile = 'data.txt';
Fid = fopen (MyFile,'rt');
A = fscanf(Fid,'%f %f',[2,inf]);
B=A';
x=B(:,1);
y=B(:,2);   
fclose(Fid);
plot(x,y,'o','MarkerSize',6,'MarkerEdgeColor','k','MarkerFaceColor','g')

init_value = 0.03;
tau = 85;
theta = 75;
gain =-0.0015;  

fprintf('Time Constant       %g s\n',tau);
fprintf('Delay               %g s\n',theta);
fprintf('Process Gain        %g \n',gain);

s = tf('s');

hold on
G_foptd = exp(-theta*s)*gain/(tau*s + 1);
t = 0:5:500;
[z t] = step(G_foptd,t);
z = z + init_value;
plot (t,z,'Linewidth',2)
grid on


hold off


