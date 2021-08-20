clear all
close all
clc
format compact

%	1.Enter data from file Points.txt to Matlab workspace
MyFile = fopen ('Points.txt','rt');
A=textscan(MyFile,'%f %f','HeaderLines',1);
A=cell2mat(A);
fclose(MyFile);

x=A(:,1);
y=A(:,2);

%	2.Draw the polygon;
figure;
hold on
plot([x;x] ,[y;y],'Color','r','Linewidth',2,'DisplayName','Polygon')

%	3.Calculate the area of the polygon, print the answer to the Command Window;
area = area_of_the_polygon(x,y);
fprintf('the area of the polygon                                   %g\n',area);

% 4.Calculate the coordinates of the centroid of the polygon,print the answer to the Command Window
[coordinates_x,coordinates_y] = coordinates_of_the_centroid(x,y,area);
fprintf('the coordinates of the centroid of the polygon           (%g,%g)\n',coordinates_x,coordinates_y);

%	2.Draw the coordinates;
plot(coordinates_x ,coordinates_y ,'o','MarkerSize',8,'MarkerEdgeColor','k','MarkerFaceColor','g','DisplayName','Center')
plot(x ,y ,'o','MarkerSize',8,'MarkerEdgeColor','k','MarkerFaceColor','r','DisplayName','Point')
legend ('Fontsize',12,'FontWeight','bold')
hold off

function area = area_of_the_polygon(x,y)
n=length(x);
area = 0;
for i = 1:n-1
    area = area + 1/2 *(x(i) * y(i+1)-x(i+1) * y(i));
end
end

function [coordinates_x,coordinates_y] = coordinates_of_the_centroid(x,y,area)
n=length(x);
coordinates_x = 0;
coordinates_y = 0;
for i = 1:n-1
    coordinates_x = coordinates_x +(x(i)+x(i+1) )* (x(i) * y(i+1)-x(i+1) * y(i))/6/area;
    coordinates_y = coordinates_y + (y(i)+y(i+1))* (x(i) * y(i+1)-x(i+1) * y(i))/6/area;
end
end
