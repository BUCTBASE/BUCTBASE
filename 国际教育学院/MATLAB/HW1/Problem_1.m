clear all
clc
close all
format compact

%   Use 1/2 inch increments for calculating the deflections
x = 0:0.5:360;
%	Calculate the defelction
for i=1:length(x)
    y(i)=(800*x(i)^3 - 13.68*10^6*x(i) - 2.5*x(i)^4 +2.5*(x(i)-120)^4*(x(i)>=120) +600*(x(i)-240)^3*(x(i)>=240))/(3.190*10^9);
end

[max_y, max_x]=max(abs(y));

%   Plot
hold on
plot(x,y,'Linewidth',2 );
plot(x(max_x),y(max_x),'o','MarkerSize',8,'MarkerEdgeColor','k','MarkerFaceColor','r')
text(x(max_x)*1.05,y(max_x)*1.05, ['(',num2str(x(max_x)),',',num2str(y(max_x)),')'])
xlabel('inch', 'FontSize', 18);
ylabel('defelction', 'FontSize', 18);
hold off
