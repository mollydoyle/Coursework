%% GEStats.m

% Chase Saca and Molly Doyle
% contains data points for the amount of change between GE's stock
% prices on every morning from 06/01/16 to 06/01/19
% fits Gaussian, Exponential, and Cauchy distributions to data
% predicts the mean, 95th percentile, and 5th percentile stock prices after
% a specified time interval and a given stock starting price

% Bad (Negative) Trend

clear all 
clc
close all

%% enter and manipulate raw data
% x is a column vector that contains the changes between each morning's 
% stock price
x = [
-0.076923
-0.028845
0.009615
-0.019232
0.134617
0.086538
-0.067308
-0.134615
-0.038462
-0.153846
0.634615
-0.326922
0.490383
0.192309
0.028846
0.115384
0.057693
-0.913462
-0.548076
0.259615
0.673076
0.144232
0.78846
-0.221153
0.019231
0.51923
0.173077
0.259615
0.048078
-0.048078
0.23077
0.25
0.125
-0.134615
0.201923
-0.221155
-0.961538
0.326923
-0.384615
-0.173076
-0.278847
0.076923
-0.153846
-0.009615
-0.076924
0.163462
0.067308
0.028845
-0.067306
0.01923
0.057693
-0.10577
0.096153
-0.153845
0.115384
-0.009615
0.067308
-0.144232
0.269232
-0.173077
-0.076923
0.076923
-0.086538
0.153845
-0.048077
-0.134615
0.096154
0.057693
-0.307693
0.009615
-0.173077
-0.788462
0.211539
-0.39423
-0.25
0.076923
0.14423
-0.105768
0.076923
0.201922
0.057693
-0.211538
-0.192309
0.307692
-0.105768
-0.201924
-0.134615
0.240385
-0.182693
-0.115385
-0.326922
-0.057693
-0.240385
0.163462
-0.134615
0.173076
-0.057691
0.125
0.028846
0.038462
-0.634617
0.538462
-0.057692
-0.336538
0.288462
-0.009617
0.576923
-0.461538
-0.134615
-0.25
-0.365385
0.60577
0.5
-0.048077
0.509615
0.615385
0.240384
-0.25
0.163461
0.048077
0.048078
-0.057693
0.23077
0.298077
0.201923
-0.115385
-0.048077
-0.096153
-0.519232
0.692309
0.067306
-0.230768
-0.173077
0.567307
-0.14423
0.211538
0.221154
-0.278847
-0.115383
0.028845
0.23077
0.153846
0.26923
-0.278846
-0.038462
0.019232
-0.048077
-0.096155
-0.105768
0.038461
0.076924
-0.173077
0.009615
0.057692
-0.173077
-0.211538
0.201923
-0.086538
-0.182694
0.038462
0.038462
-0.471154
-0.25
-0.615385
0.538462
0.01923
-0.03846
-0.423078
-0.105769
-0.115385
-0.14423
0.201922
-0.105768
0.067308
-0.23077
0.009615
0.211538
0.134617
0.240383
0.153847
0.057692
0.057693
0
0.105768
-0.461538
-0.192307
0.201922
-0.057692
-0.009615
0.240385
-0.038461
-0.182694
-0.067306
-0.038462
-0.134615
0.086538
0.375
-0.451923
-0.201923
0.240385
0.048076
0.048077
-0.038462
-0.288461
-0.057692
0.086538
-0.134615
-0.134616
0.201923
0.134615
0.192308
-0.096153
0.134615
0.182692
-0.086539
-0.076923
0.144232
-0.067309
-0.115383
-0.173078
-0.076922
-0.019232
0.278847
0.153845
0.21154
-0.403847
-0.384615
0.067307
-0.221153
-0.182692
-0.08654
0
-0.086538
0.336538
-0.134615
0.028847
-0.076924
-0.153846
-0.230769
-0.307693
-0.278845
0.173077
-0.413462
-0.538462
0.278847
0.653845
-0.01923
0.10577
-0.509617
-0.317306
-0.144232
0.019232
0.173076
0.346154
0.028846
0.076924
-0.028847
-0.259615
-0.048077
1.548077
-0.115385
-0.615385
0
0.48077
-0.019232
-0.240383
-0.509617
-0.39423
0.01923
-0.192306
-0.067309
-0.25
-0.096153
-0.067308
0.067308
0.365385
-0.653847
-0.586538
-0.115385
-0.096153
0.490383
0.038462
0.153846
0.019232
0
0.086538
0.163462
-1.576923
0.384615
-0.201924
0.019232
0
0.259615
-0.307693
0.086538
-0.182692
0.144232
0.153845
-0.009615
-0.10577
-0.076922
0.153845
-0.298076
-0.115385
-0.067307
-0.086538
-0.048077
-0.423078
-0.134615
0.076923
-0.048077
-0.086538
-0.038462
0.134615
-0.192308
0.153847
-0.076924
0.182694
0.442306
-0.163461
-0.365384
-0.538461
-0.144232
0.019232
0.105768
0.163462
0
-0.134615
0.480768
-0.25
0.125
0.490385
0.076923
0.221154
-0.14423
-0.586539
-0.163461
0
0.375
0.259615
-0.471154
0.01923
-0.298076
-0.384615
-0.548077
-0.076923
0.096153
-0.153845
0.221153
-0.019231
-0.057692
-0.961538
1.25
-1.269232
-0.26923
-0.259615
-0.298077
-0.615385
-0.346153
-0.182693
-0.01923
-0.125
0.576923
-0.33654
0.038462
-0.163462
-0.057692
0.269232
-1.413462
-1.23077
0.932692
-0.134615
-0.375
0
0.192308
0.221154
-0.038462
-0.163462
0.269232
0.105768
-0.26923
-0.269231
-0.211539
-0.163461
0.192308
-0.086538
-0.10577
0.326923
-0.028845
-0.144232
0.009615
0.086539
-0.096154
-0.134615
-0.163461
0.048076
-0.057691
0.009615
-0.10577
-0.076922
0.298077
0.692306
0.076924
0.461538
-0.182692
-0.326923
0.25
0.615385
-0.10577
-0.76923
-0.644232
-0.240383
-0.721155
-0.721153
0.384615
0.673076
-0.480768
-0.35577
-0.105769
0.076923
-0.038462
0
-0.163461
-0.394231
-0.634615
0.471154
-0.115385
-0.480769
0.355769
-0.307692
-0.048077
0.230769
-0.076923
0.067308
-0.201923
-0.173077
0
-0.134616
0.269231
-0.067307
-0.423077
-0.163462
0.182692
0.403847
-0.115385
0.01923
0.115386
0.384614
-0.317307
-0.221154
-0.144231
0.028847
-0.076924
-0.153845
-0.423078
0.086539
-0.336539
-0.163461
-0.298077
0.576923
0.057693
-0.125
-0.317308
-0.288462
0.451923
0.028847
-0.211539
-0.086539
-0.096153
0.115384
0.365385
0.086538
-0.115384
0.480769
-0.201923
1.221154
-0.182692
-0.086539
0.057692
-0.586539
0.10577
0.14423
-0.278845
0.019231
0.086538
-0.307693
0.211539
0.086538
0.163462
0.39423
-0.01923
-0.038462
0
0.009616
0.394231
-0.038462
0.269231
0.028846
-0.182692
-0.826923
0.259615
-0.125
-0.326923
-0.038461
0
0.028845
-0.403845
0.105769
-0.182693
0.144231
0.201923
0.038462
-0.009616
-0.144231
-0.346153
-0.288462
-0.14423
-0.288462
0.048076
-0.048076
0.259615
0.413461
0.384616
0.076923
-0.105769
-0.336539
-0.125
0.028847
-0.009616
0.548077
0.057692
0.057693
-0.009616
-0.076922
-0.076924
-0.038462
-0.105769
-0.019231
0
-0.673076
-0.096154
0.201923
-0.028846
0.019231
-0.076923
0.144231
0.346153
-0.365384
-0.019231
-0.028846
0
0.067308
-0.173078
-0.096153
-0.182693
-0.230769
-0.201923
-0.009615
0
0.009615
0.067308
0.259615
-0.192307
0.105769
-0.038462
0.278846
0
0.096154
-0.134615
0.14423
-0.413461
0.048077
-0.105769
-0.028847
0.076923
-0.134615
0.35577
-0.134616
0.076923
0.057693
-0.048078
-0.028846
-0.182692
-0.288462
-0.355769
-0.461539
0.115386
0.067307
1.519231
-0.673077
0.019231
0.067308
0.451922
0.615385
0.182693
-0.307693
-0.259615
-0.567308
-0.269231
-0.019231
0.019231
-0.105769
0.134616
0.298076
-0.423076
0.538461
-0.490385
-0.586538
-0.153846
-0.836539
-0.365384
-0.163462
-0.375
-0.221154
-0.028846
0.086538
-0.298076
-0.336539
-0.355769
-0.384616
0.711539
-0.5
-0.153846
-0.086538
-0.307693
0.115385
-0.009616
-0.163462
-0.115384
-0.096154
0.25
0.009616
-0.115385
0.201923
-0.528846
0.096154
-0.317308
0.067308
-0.192308
0.625
-0.39423
0.009614
0.086539
0.442308
0.009615
-0.317307
-0.25
-0.067308
0.182692
0.009616
0.317307
-0.057692
0.538461
0.163462
0.346154
0.346153
-0.375
-0.01923
0.355769
-0.057692
0.096153
-0.192307
0.182693
0.317307
-0.240385
-0.278846
-0.057692
0.211538
0.125
-0.076922
0.076922
0.923078
0.25
0.067307
-0.019231
0.403846
-0.240384
-0.394231
-0.134615
0.192308
-0.086539
0.298077
-0.163462
-0.086538
0.057692
-0.057692
0.019231
1.461538
-0.335
0.04
-0.01
-0.37
-0.13
0.06
-1.12
-0.18
0.25
0.12
0.48
-0.2
0.57
-0.01
-0.3
0.23
-0.09
0.07
0.02
-0.26
-0.01
0.13
-0.12
0.02
0.04
0.04
0.2
-0.16
-0.03
-0.56
-0.16
-0.1
-0.13
0.03
-0.14
0.03
0.12
-0.03
0.12
0.05
0.01
-0.09
-0.1
0.45
0.66
-0.08
0
0.15
-0.06
0.1
-0.26
0.03
-0.09
-0.17
0.09
0.21
0.07
-0.21
-0.1
0.05
-0.01
-0.14
-0.19
-0.21
-0.1
0.06
-0.03
];

% make raw data into row vector called GEChanges
GEChanges = x.';

% make histogram of raw data points (the changes between mornings)
xbins = -2:0.1:2;
figure(1)
histogram(GEChanges,xbins,'FaceColor','y');
hold on
grid on;

% plot histogram as a line
[yy,xx] = hist(GEChanges,xbins);
plot(xx,yy,'k','LineWidth',1);
title('Histogram and Line of Raw Data - GE','FontSize',13);

%% fit Gaussian, Exponential, and Cauchy distributions to data

% set parameters for all 3 distributions
meanStocks = mean(GEChanges); % mean of data
variance = var(GEChanges); % variance of data
standardDeviation = std(GEChanges); % standard deviation of data
maxPoint = max(yy); % max y-value of histogram line (peak)
N=length(GEChanges); % length of data set --> 755 data points

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
title('Gaussian Distribution - GE','FontSize',13);
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

pear = find(GEChanges > 0);
peach = GEChanges(pear); % positive raw data points 
lambda = 1 / (mean(peach) - meanStocks);

subplot(3,1,2)
% plot both positive and negative sides of exponential line
plot(xxx,A*exp(B*xxx),'r*');
hold on
plot(-xxx,A*exp(B*xxx),'r*');

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
title('Exponential Distribution - GE','FontSize',13);
legend('Exponential Line','Exponential Line','Raw Data Line');
grid on

%% cauchy distribution

gam = 0.1; % trial-and-error method to find this value of gamma

% iterate through xCauch in order to generate cauchy distributed
% x-values for the cauchy distribution
for i=1:1:N
    xCauch(i) = gam * tan(pi*rand - 0.5*pi) + meanStocks;
end

edges = linspace(-2, 2, 41);
[yc,xc]=hist(xCauch,edges);
errorCauch = mean((yc - yy).^2);

subplot(3,1,3)
plot(xx,yy,'k','LineWidth',1); % plot raw data line
hold on
plot(xc,yc,'b--','LineWidth',1); % plot line of cauchy distribution

% plot the histogram of cauchy distribution
histogram(xCauch,'BinEdges',edges,'FaceColor','g');
title('Cauchy Distribution - GE','FontSize',13);
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
title('Gaussian Prediction - GE');
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

% plot mean and 95th and 5th percentiles , scale accordingly
subplot(3,1,2)
plot(meanExp+StockStartingPrice);
hold on
plot(percExpHigh+meanExp+StockStartingPrice,'k--');
plot(percExpLow+meanExp+StockStartingPrice,'k--');
legend('Mean','95th Percentile','5th Percentile');
title('Exponential Prediction - GE');
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
title('Cauchy Prediction - GE');
grid on

%% predict the stock price average, low, and high on the final day of the 
% time interval

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

disp(['GE Starting Stock Price: ',num2str(StockStartingPrice)]);
disp(['GE Average Predicted Stock Price: ',num2str(predictionMean)]);
disp(['GE 95th Percentile Predicted Stock Price: ',num2str(predictionHigh)]);
disp(['GE 5th Percentile Predicted Stock Price: ',num2str(predictionLow)]);

