function [fitresult, gof] = createFits(Year, Population)
%CREATEFITS(YEAR,POPULATION)
%  Create fits.
%
%  Data for 'untitled fit 1' fit:
%      X Input : Year
%      Y Output: Population
%  Data for 'untitled fit 2' fit:
%      X Input : Year
%      Y Output: Population
%  Output:
%      fitresult : a cell-array of fit objects representing the fits.
%      gof : structure array with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 21-Jul-2021 20:14:08 自动生成

%% Initialization.

% Initialize arrays to store fits and goodness-of-fit.
fitresult = cell( 2, 1 );
gof = struct( 'sse', cell( 2, 1 ), ...
    'rsquare', [], 'dfe', [], 'adjrsquare', [], 'rmse', [] );

%% Fit: 'untitled fit 1'.
[xData, yData] = prepareCurveData( Year, Population );

% Set up fittype and options.
ft = fittype( 'poly1' );

% Fit model to data.
[fitresult{1}, gof(1)] = fit( xData, yData, ft );

% Plot fit with data.
figure( 'Name', 'untitled fit 1' );
h = plot( fitresult{1}, xData, yData );
legend( h, 'Population vs. Year', 'untitled fit 1', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
xlabel( 'Year', 'Interpreter', 'none' );
ylabel( 'Population', 'Interpreter', 'none' );
grid on

%% Fit: 'untitled fit 2'.
[xData, yData] = prepareCurveData( Year, Population );

% Set up fittype and options.
ft = fittype( 'smoothingspline' );

% Fit model to data.
[fitresult{2}, gof(2)] = fit( xData, yData, ft );

% Plot fit with data.
figure( 'Name', 'untitled fit 2' );
h = plot( fitresult{2}, xData, yData );
legend( h, 'Population vs. Year', 'untitled fit 2', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
xlabel( 'Year', 'Interpreter', 'none' );
ylabel( 'Population', 'Interpreter', 'none' );
grid on


