clear
clc

Year = [1750 1800 1850 1900 1950 1990 2000 2009];
Population = [791 980 1260 1650 2520 5270 6060 6800];
x=1750:1:2009;
%cftool(Year,Population)

%the exponential function
a = 9.911e-08;
b = 0.01241;
exponential = @(x)a*exp(b*x);

%third-order polynomial
p1= 0.001020697301838;
p2= -5.604096642832609;
p3= 1.025536170980091e+04;
p4= -6.253911927981189e+06;
thirdorder = @(x)p1*x^3 + p2*x^2 + p3*x + p4;

% linear and spline interpolations
linear(x)=interp1(Year,Population,x,'linear');
spline(x)=interp1(Year,Population,x,'spline');

exponential(1980)
thirdorder(1980)
linear(1975)
spline(1975)

figure
hold on
plot(Year ,Population ,'o','Color','r','DisplayName','Origin')
fplot(exponential,[1750 2009],'-','DisplayName','exponential')
legend ('Fontsize',12,'FontWeight','bold')
hold off

figure
hold on
plot(Year ,Population ,'o','Color','r','DisplayName','Origin')
fplot(thirdorder,[1750 2009],'-','DisplayName','thirdorder')
legend ('Fontsize',12,'FontWeight','bold')
hold off

figure
hold on
plot(Year ,Population ,'o','Color','r','DisplayName','Origin')
plot(x,linear(x),'-','DisplayName','exponential')
legend ('Fontsize',12,'FontWeight','bold')
hold off

figure
hold on
plot(Year ,Population ,'o','Color','r','DisplayName','Origin')
plot(x,spline(x),'-','DisplayName','exponential')
legend ('Fontsize',12,'FontWeight','bold')
hold off






