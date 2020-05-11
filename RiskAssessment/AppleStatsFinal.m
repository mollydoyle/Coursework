%% AppleStats.m

% Chase Saca and Molly Doyle
% contains data points for the amount of change between Apple's stock
% prices on every morning from 06/01/16 to 06/01/19
% fits Gaussian, Exponential, and Cauchy distributions to data
% predicts the mean, 95th percentile, and 5th percentile stock prices after
% a specified time interval and a given stock starting price

% Good (Positive) Trend

clear all
clc
close all

%% enter and manipulate raw data
% x is a column vector that contains the changes between each morning's 
% stock price
x = [
-0.580001
-1.419999
0.190003
0.199997
1.260002
-0.230003
-0.519997
0.029999
0.160003
-1.370002
0.5
-1.370003
0.170006
-0.620003
-1.059998
1.309998
-0.309998
-3.029998
0.089996
-0.099998
1.069999
0.470001
1.049996
-0.099999
-0.790001
1.099999
0.790001
0.260002
0.419998
0.240006
-0.020005
1.529999
-0.220001
0.860001
0.440002
-0.169998
-0.57
-1.010002
-1.43
7.449997
-1.439995
1.36
0.220002
1.639999
-1.240005
0.770004
0.689995
1.25
0.710006
0.479996
-0.190002
-0.739998
0.36
1.489998
-0.529999
0.130005
-0.460006
0.090004
-0.270005
-0.019996
-1.180001
0.020005
-0.790001
-0.82
-0.139999
0.479995
1.559998
0.200005
-0.07
-0.580002
-2.610001
-1.989997
4.86
1.220001
5.129998
1.260002
0.069999
-2.139999
0.799995
0.5
0.07
-2.779999
1.360001
0.690002
-0.529998
-0.700005
0.25
0.349999
0.340004
0.299995
0.610001
0.709999
2.68
-0.349999
-0.559997
1.089996
-0.549995
0.849998
-0.93
-0.389999
-0.050003
0.29
0.849999
-3.639999
1.080001
-1.519996
-0.220001
-0.190003
-2.059997
-0.419999
-2.450004
1.550003
0.229996
-0.430001
1.209999
-3.969993
0.589996
-1.139999
0.129997
3.110001
-0.089997
0.400002
1.829994
-0.589996
-0.230004
0.300003
-0.650001
0.819999
-1.229995
-1.200005
0.830002
-0.5
-0.239998
1.599999
1.449997
0.980003
0.549995
1.200005
0.339996
1.090004
-0.669998
0.939995
0.060005
-0.450005
-0.760002
0.930001
1
-1.07
0.200005
-0.849999
0.049995
0.07
0.860001
1.169998
0.82
-0.029999
0.160004
0.209999
-0.770005
1.660004
-0.599998
1.049995
-0.449997
-0.449997
0.869995
1.25
0.470001
-1.209999
0.220002
5.879997
0.950004
0.329995
0.820007
1.409988
0.810013
0.299988
0.810013
0.619995
0.389999
2.050003
0.149994
-0.569992
1.12999
0.199997
0.950012
-1.470001
1.229995
-0.059997
0.809997
2.110001
-1.220001
0.589996
-0.309997
-0.110001
-0.209992
0.509995
-0.399994
0.449997
0.110001
1.309997
0.279999
-0.600006
1.710007
-2.259995
1.409989
0.240005
-2.110001
1.520005
2.769989
0.510009
-0.470001
-0.009994
-0.460007
0.970001
0.069992
-0.559997
-0.12999
-0.660004
-1.339996
0.309998
-0.430008
-0.069992
0.470001
-0.660004
1.220001
1.059998
0.410004
0.559997
-0.550003
0.169998
1.01001
2.439987
-1.949997
0.930008
0.239991
2.270004
4.839996
-0.23999
-1.180008
2.25
1.309998
-0.069993
-2.339996
-2.330002
2.110001
0.619995
0.899994
-1.059998
-0.11
0.270004
-0.580002
0.550003
-0.800003
0.410004
0.759994
-0.440002
1.12001
0.229996
-0.059998
-9.449997
1.419999
0.339996
-4.179993
0.459992
-0.119995
3.209991
-1.349991
0.25
-0.639999
2.039993
-2.160003
-0.51999
0.220002
-0.26001
0.430008
-1.190003
-0.669998
-0.12001
1.210007
0.619995
1.139999
-0.369995
2.470001
0.850006
0.37999
1.279999
1.020004
-1.509995
0.589997
1.220001
1.550003
0.399994
-3.860001
0.009995
-0.799988
10.179993
-2.229996
-0.979996
0.989991
1.540008
0.659989
0.639999
-3.299988
2.720001
1.339997
1.279998
-1.419998
-2.660003
-0.360001
0.729996
0.840011
1.359986
-0.779999
0.490005
-0.039993
3.699997
-0.160004
1.160004
-1.050003
-1.039993
-0.620011
-1.229995
-0.360001
2.110001
-2.740006
-0.87999
-0.520004
1.64
-0.600006
-1.610001
-2.099991
-4.26001
-1.549988
1.789994
2.020004
0.089996
-0.679992
1.049988
-0.25
-0.37999
0.549988
0.790008
0.839997
0.25
-0.089997
0.380005
0.37999
1.169998
1.880005
0.639999
-3.669998
-0.139999
0.279998
-0.600006
0.620011
0.319992
2.059997
4.600006
4.009995
1.970001
-3.269989
7.399994
-1.630005
1.540009
0.75
0.449997
0
-1.610001
-0.460007
-3.069992
1.209992
-0.14
-0.75
0.490006
2.580002
1.740005
-0.050003
-0.75
-1.669998
-2.200012
-0.479996
2.529999
-3.419998
-1.559998
1.529999
1.460006
-1.290008
2.949997
0.350006
-0.100006
1.230011
1.25
0.149994
-0.160004
-0.699997
0.509995
-3.87999
-0.699997
0.899994
-0.479996
-0.36
2.369995
0.009994
0.900009
0.910004
0.199997
-1.389999
1.429992
1.589997
1.720001
-1.75
3.220001
-0.759994
-1.309998
0
-0.050003
-2.740005
-2.509995
-1.839996
-4.630005
1.339996
0.300003
-1.169998
-6.899994
-4.270004
8.259994
-2.800003
-3.219986
1.429993
3.449997
1.089996
6.75
2.570008
-0.309998
0.779999
-1.029999
1.869995
2.680008
2.75
0.159989
-0.720002
-5.73999
2.410004
2.699997
-2.970002
0.539994
2.480011
2.329986
2.300003
-2.269989
-1.820007
0.149994
-1.329987
-2.080002
-0.200012
-5.039993
-1.610001
-0.319992
5.609986
-6.429993
0.559998
-1.169999
1
-2.759994
7.699997
-1.610001
-1.089996
3.119995
-0.770004
1.180008
1.369995
0.25
1.460006
1.319993
-4.050003
-3.159989
-3.770004
-1.160004
-3.050003
1.5
-0.119995
-1.869995
4.279999
8.819992
0.650009
2.369995
6.929993
-0.189988
1.559998
1.190002
1.75
-0.48001
-2.229996
-0.709992
1.929993
-0.809998
0.809998
0.380005
-2.029999
2.419998
-0.540008
-0.62999
0.119995
-0.5
0.770004
3.649994
1.430008
0.559998
0.509994
-2.970001
0.180008
0.039993
1.029999
-0.869995
-1.520004
-2.149994
-2.740006
1.210007
0.899994
-1.130005
-2.720001
-0.409989
2.239991
-1.12999
2.189987
-2.469986
3.969986
-2.529998
0.160003
4.080002
1.210007
-2.210007
1.029999
1.550003
0.440002
-1.770004
2.029999
-2.089997
2.089997
-1.100006
1.770004
0.610001
1.550003
0.380004
-3.090011
-1.599991
8.830002
1.449997
6.449997
0.970001
1.320007
-3.270004
1.229996
0.080002
0.339996
2.460007
-0.940003
2.529999
1.690002
4.660004
-1.300003
-2.699997
0.549988
1.950012
0.549988
1.860001
1.139999
3.100006
3.259995
1.900009
0.580001
-2.760009
-4.37999
-0.900009
-2.940002
6.930007
-1.419998
2.229996
-3.600006
-4.360001
0.710007
1.740005
0.539994
-3.959992
2.929993
1.25
2.820007
0.969986
3.160004
-0.699997
2.800003
0.729996
-2.819992
-5.75
1.429992
1.820008
-10.940003
5.899994
0.740006
-2.230011
3.37001
-4.440002
0.199997
1.729995
-3.959991
6.770004
-4.889999
-1.810013
3.290008
-8.040008
5.730011
2.169998
-9.5
-5.25
-2.380005
4.050003
4.009995
-4.429993
-6.550003
-7.369995
2.269989
-5.509995
2.110001
-0.5
-11.630005
1.360001
-4.789994
-0.699997
-2.73001
5.220001
5.930008
-2.370011
4.170014
-3.51001
-9.190002
1.73001
-8.490005
6.660004
-1.26001
0.090011
-1.490005
-3.550003
-0.069992
0.619995
-5.600006
-3.539993
-8.710007
0.150009
7.539993
1.660004
1.029999
-3.64
-10.910003
0.550003
4.169998
0.860001
1.729995
1.210007
0.380005
-2.029999
-0.580002
2.809998
1.119995
3.300003
-1.089996
-2.26001
-0.039993
1.369995
0.309997
0.460007
7
2.860001
0.850006
0.449997
5.449997
1.789993
-2.25
-3.409989
2.059998
-0.949997
1.289993
-1.679992
1.539993
-1.539993
1.479995
0.610001
-0.220001
2.580002
-0.449997
-0.5
1.11
-0.040008
1.410003
0.25
-1.270004
-0.800003
-3.549988
5.169998
4.509995
2.25
1.649994
0.950012
0.949997
2.550003
-2.12001
3.790008
5.319992
-3.830001
0.150009
-2.910004
0.199997
0.880005
1.809997
-0.550003
2.160004
1.539993
1.660004
-0.029999
3.900009
-1.640014
2.170013
-1.650009
-0.619995
0.880005
0.079986
3.580002
-0.289993
1.599991
2.930008
-0.529999
-1.930008
-0.5
-1.339996
6.820007
-0.040009
1.050003
-6.600006
1.590012
-3.980011
-1.5
-2.979996
-9.709991
-1.300003
-0.14
3.64
-2.980011
-3.409989
1.699997
-0.559997
-4.860001
0.399994
-1.279999
-2.5
1.529999
-1.720001
];

% make raw data into row vector called AppleChanges
AppleChanges = x.';

% make histogram of raw data points (the changes between mornings)
xbins = -15:15;
figure(1)
histogram(AppleChanges,xbins,'FaceColor','y');
hold on
grid on;

% plot histogram as a line
[yy,xx] = hist(AppleChanges,xbins);
plot(xx,yy,'k','LineWidth',1);
title('Histogram and Line of Raw Data - Apple','FontSize',13);

%% fit Gaussian, Exponential, and Cauchy distributions to data

% set parameters for all 3 distributions
meanStocks = mean(AppleChanges); % mean of data
variance = var(AppleChanges); % variance of data
standardDeviation = std(AppleChanges); % standard deviation of data
maxPoint = max(yy); % max y-value of histogram line (peak)
N=length(AppleChanges); % length of data set --> 755 data points

figure(2)

%% gaussian distribution 

% initialize vector of zeros that will hold the normally distributed
% x-values for the gaussian distribution
xGaus = zeros(1,N);

% iterate through xGaus and generate the normally distributed numbers
for i=1:1:N
    xGaus(i) = randn * standardDeviation + meanStocks;
end

subplot(3,1,1)
hold on
plot(xx,yy,'k','LineWidth',1); % plot raw data line

% plot gaussian distribution as a histogram and its line
[yyG,xxG] = hist(xGaus,xbins);
plot(xxG,yyG,'b--','LineWidth',1);
histogram(xGaus,xbins,'FaceColor','c');
title('Gaussian Distribution - Apple','FontSize',13);
legend('Raw Data Line','Gaussian Distribution');
grid on

%% exponential distribution
A = maxPoint;

apple=find(xx>0); % find positive x-values of raw data line
xxx=xx(apple); % positive x-values
yyy=yy(apple); % corresponding y-values to positive x-values

orange=find(yyy>0); % find positive y-values that correspond to positive x-values
xxx=xxx(orange); % positive x-values that correspond to positive y-values
yyy=yyy(orange); % positive y-values that correspond to positive x-values
    
pexp = polyfit(xxx,log(yyy),1); % best fit exponential line
B = pexp(1); % best fit B value
errorexp=mean((yy-A*exp(B*xx)).^2); % error of best fit exponential line

subplot(3,1,2)
% plot both positive and negative sides of exponential line
plot(xxx,A*exp(B*xxx),'r*');
hold on
plot(-xxx,A*exp(B*xxx),'r*');


pear = find(AppleChanges > 0);
peach = AppleChanges(pear); % positive raw data points 
lambda = 1 / (mean(peach) - meanStocks); 

U=rand(1,N); % generate vector of random numbers 

% iterate through xExp and U in order to generate exponentially
% distributed x-values for the exponential distribution
for i=1:1:N
    % if random number >= 0.5 , take the positive x-value
    if rand(1) >= 0.5
        xExp(i) = log(-U(i)+1) / -lambda;
    else % if random number < 0.5 , take the negative x-value
        xExp(i) = - log(-U(i)+1) / -lambda;
    end
    % shift x-values in order to match raw data
    xExp(i) = xExp(i) + meanStocks;
end

% plot raw data line and histogram of exponential distribution 
plot(xx,yy,'k');
histogram(xExp,xbins,'FaceColor','m');
title('Exponential Distribution - Apple','FontSize',13);
legend('Exponential Line','Exponential Line','Raw Data Line');
grid on

%% cauchy distribution

gam = 1.2; % trial-and-error method to find this value of gamma

% iterate through xCauch in order to generate cauchy distributed
% x-values for the cauchy distribution
for i=1:1:N
    xCauch(i) = gam * tan(pi*rand - 0.5*pi) + meanStocks;
end

edges = linspace(-15, 15, 31);
[yc,xc]=hist(xCauch,edges);
errorCauch = mean((yc - yy).^2);

subplot(3,1,3)
plot(xx,yy,'k','LineWidth',1); % plot raw data line
hold on
plot(xc,yc,'b--','LineWidth',1); % plot line of cauchy distribution

% plot the histogram of cauchy distribution
histogram(xCauch,'BinEdges',edges,'FaceColor','g');
title('Cauchy Distribution - Apple','FontSize',13);
legend('Raw Data Line','Cauchy Distribution');
grid on

%% predict the stock price after a given time period per distribution
timeDays = 30; % time interval for which you want to predict stock price after 
StockStartingPrice = 100; % price of stock when time interval starts  

figure(3)

%% gaussian prediction
% initialize matrix that will hold stock price predictions each day 
% over entire interval and through 100 simulations of that time interval
stockPriceGauss = zeros(100,timeDays); 

% generate normally distributed changes from morning-morning 
for i=1:1:100
    for p=1:1:timeDays
        randNums = randn(1,timeDays);
        gaussPredict(i,p) = randNums(p) * standardDeviation + meanStocks;
    end
end

% generate stock price per day over entire time interval for 100 simulations
for i=1:1:100
    for p=1:1:timeDays
        stockPriceGauss(i,p+1)=stockPriceGauss(i,p)+gaussPredict(i,p);
    end
end

meanGauss = mean(stockPriceGauss); % mean stock prices per each day 
percGaussHigh = prctile(stockPriceGauss,95); % 95th percentile stock prices per each day 
percGaussLow = prctile(stockPriceGauss,5); % 5th percentile stock prices per each day 

% plot mean and 95th and 5th percentiles , scale accordingly
subplot(3,1,1)
plot(meanGauss+StockStartingPrice);
hold on
plot(percGaussHigh+meanGauss+StockStartingPrice,'k--');
plot(percGaussLow+meanGauss+StockStartingPrice,'k--');
legend('Mean','95th Percentile','5th Percentile');
title('Gaussian Prediction - Apple');
grid on

%% exponential prediction
% initialize matrix that will hold stock price predictions each day 
% over entire interval and through 100 simulations of that time interval
stockPriceExp = zeros(100,timeDays);

% generate exponentially distributed changes from morning-morning 
for i=1:1:100
    for p=1:1:timeDays
        randNums = rand(1,timeDays);
        if rand > 0.5
            expPredict(i,p) = log(-randNums(p)+1) / -lambda;
        else 
            expPredict(i,p) = - log(-randNums(p)+1) / -lambda;
        end
        expPredict(i,p) = expPredict(i,p) + meanStocks;
    end
end

% generate stock price per day over entire time interval for 100 simulations
for i=1:1:100
    for p=1:1:timeDays
        stockPriceExp(i,p+1)=stockPriceExp(i,p)+expPredict(i,p);
    end
end

meanExp = mean(stockPriceExp); % mean stock prices per each day
percExpHigh = prctile(stockPriceExp,95); % 95th percentile stock prices per each day
percExpLow = prctile(stockPriceExp,5); % 5th percentile stock prices per each day

% plot mean and 95th and 5th percentiles , and scale accordingly
subplot(3,1,2)
plot(meanExp+StockStartingPrice);
hold on
plot(percExpHigh+meanExp+StockStartingPrice,'k--');
plot(percExpLow+meanExp+StockStartingPrice,'k--');
legend('Mean','95th Percentile','5th Percentile');
title('Exponential Prediction - Apple');
grid on

%% cauchy prediction
% initialize matrix that will hold stock price predictions each day 
% over entire interval and through 100 simulations of that time interval
stockPriceCauch = zeros(10000,timeDays);

% generate cauchy distributed changes from morning-morning 
for i=1:1:10000
    for p=1:1:timeDays
        randNums = rand(1,timeDays);
        cauchPredict(i,p) = gam * tan(pi*randNums(p) - 0.5*pi) + meanStocks;
    end
end

% generate stock price per day over entire time interval for 100 simulations
for i=1:1:10000
    for p=1:1:timeDays
        stockPriceCauch(i,p+1)=stockPriceCauch(i,p)+cauchPredict(i,p);
    end
end

% plot mean and 95th and 5th percentiles , and scale accordingly
subplot(3,1,3)
% if the mean stock price is negative, set to zero (company is bankrupt)
meanCauch = mean(stockPriceCauch);
for jj=1:1:length(meanCauch)
    if meanCauch(jj) < 0
        meanCauch(jj) = 0;
    end
end
plot(meanCauch+StockStartingPrice);
hold on
percCauchHigh = prctile(stockPriceCauch,95);
percCauchLow = prctile(stockPriceCauch,5);
% if the 95th percentile stock price is negative, set to zero (company is bankrupt)
kiwi = percCauchHigh + meanCauch + StockStartingPrice;
for kk=1:1:length(kiwi)
    if kiwi(kk) < 0
        kiwi(kk) = 0;
    end
end
plot(kiwi,'k--');
% if the 5th percentile stock price is negative, set to zero (company is bankrupt)
mango = percCauchLow + meanCauch + StockStartingPrice;
for qq=1:1:length(mango)
    if mango(qq) < 0
        mango(qq) = 0;
    end
end
plot(mango,'k--');
legend('Mean','95th Percentile','5th Percentile');
title('Cauchy Prediction - Apple');
grid on

%% predict the stock price average, low, and high on the final day of the time interval
% mean prediction
mC = meanCauch(timeDays+1) + StockStartingPrice;
mE = meanExp(timeDays+1) + StockStartingPrice;
mG = meanGauss(timeDays+1) + StockStartingPrice;

predictionMean = (1/3)*(mC) + (1/3)*(mE) + (1/3)*(mG);

% high prediction
hC = kiwi(timeDays+1);
hE = percExpHigh(timeDays+1) + meanExp(timeDays+1) + StockStartingPrice;
hG = percGaussHigh(timeDays+1) + meanGauss(timeDays+1) + StockStartingPrice;

predictionHigh = (1/3)*(hC) + (1/3)*(hE) + (1/3)*(hG);

% low prediction
lC = mango(timeDays+1);
lE = percExpLow(timeDays+1) + meanExp(timeDays+1) + StockStartingPrice;
lG = percGaussLow(timeDays+1) + meanGauss(timeDays+1) + StockStartingPrice;

predictionLow = (1/3)*(lC) + (1/3)*(lE) + (1/3)*(lG);

disp(['Apple Starting Stock Price: ',num2str(StockStartingPrice)]);
disp(['Apple Average Predicted Stock Price: ',num2str(predictionMean)]);
disp(['Apple 95th Percentile Predicted Stock Price: ',num2str(predictionHigh)]);
disp(['Apple 5th Percentile Predicted Stock Price: ',num2str(predictionLow)]);

