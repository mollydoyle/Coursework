%% FacebookStats.m

% Chase Saca and Molly Doyle
% contains data points for the amount of change between Facebook's stock
% prices on every morning from 06/01/16 to 06/01/19
% fits Gaussian, Exponential, and Cauchy distributions to data
% predicts the mean, 95th percentile, and 5th percentile stock prices after
% a specified time interval and a given stock starting price

% Mediocre (Flat) Trend

clear all 
clc
close all

%% enter and manipulate raw data
% x is a column vector that contains the changes between each morning's 
% stock price
x = [
-0.959999
0.190002
0.290001
-0.36
0.619995
-1.479996
0.369995
-0.589996
-2.540001
-0.93
1.230003
-1.43
0.549995
-0.650001
0.350006
0.529999
-0.279999
-3.360001
0.559998
-0.940003
2.740006
1.299995
-0.470001
-0.259995
-0.580001
3.269996
-0.199997
1.279999
0.919998
-0.239998
-0.889999
0.239998
-0.419998
1.669998
2.260002
0.669998
-2.019996
1.489997
0.610001
0.419998
5.099999
-2.869995
-0.800004
0.21
-0.970002
-0.149994
2.040001
0.269997
0.089996
-0.269996
0.129997
-0.5
0.210007
-1.410004
0.160004
0.349998
-0.410004
-0.269996
1.18
-0.040001
-1.349998
0.93
0.299995
2.25
-1
0.779999
0.470001
-0.18
3.369995
0.880005
-1.209991
-3.750008
2.07
-1.14
1.090004
0.219994
1.710007
-1.26001
0.480011
1.369995
-2.940002
-0.189995
0.239998
1.600006
-0.030014
-1.149994
0.350006
0.789993
-0.919998
0.179993
0.61
0.64
0.550003
-1.220001
-0.799988
0.279998
-0.290008
0.479996
0.060012
1.330002
-0.290008
2.940002
0.779999
-1.860001
0.100006
-1.240005
1.509995
-0.599991
-1.180008
-8.229996
-2.410004
3.240006
-0.800003
-0.529999
2.43
-4.400001
-0.400002
-2.399994
-2.25
2.329995
1.580001
-0.190002
4.200005
-1.169999
-0.220001
-0.889999
0.449997
-0.25
-1.940003
-3.269996
0.839996
1.740005
-0.690002
0.980003
1.239998
0
-1.36
2.139999
0.080002
0.82
-1.050004
-0.349998
-0.580002
-0.059997
-1.860001
-0.040001
1.230003
-1.190002
-0.400002
-0.569999
1.520004
1.309998
2.120002
2.57
1.269997
-0.470002
1.260003
1.879997
0.549995
0.370011
-0.180008
-0.12999
-0.790008
2.070007
0.619995
1.630005
1.049988
-1.099991
-1.410004
2.080002
0.970001
-1.979996
-0.260009
1.260009
0.360001
1.889999
-0.389999
0.599991
-0.599991
-0.650009
-0.37999
0.429993
0
0.100006
2.289993
-1.729995
1.099991
1.529998
-0.319992
0.619995
-0.459991
0.25
0.149994
0.119995
0.570007
1.190003
-0.199997
0.75
-0.170014
0.910004
0.139999
-0.629989
1.439987
-3.220001
1.550003
0.600006
-1.029999
1.309998
1.630004
0.409989
-0.089996
-0.380005
-0.069992
0.399994
-0.149994
-0.910004
-0.199997
-0.199997
-1.080002
-0.100006
0.14
1.510009
0.080002
1.599991
0.949997
1.060013
0.829986
1.300003
-0.419998
2.830002
2.240005
1.599991
0.26001
-3.430008
1.279999
-0.73999
0.779998
-1.260009
0.080002
0.089996
-0.229996
-0.059997
-2.110001
-3.279999
3.729996
-0.369995
0.440002
-0.010009
1.790008
1.929993
-0.259995
0.729996
-0.949997
0.100006
1.789993
-0.229995
-0.14
0.809998
0.690002
-6.600006
1.979996
1.110001
-3.589997
1.919998
2.120011
1.169998
-0.520004
0.649994
-0.289994
3.529999
-3.410004
-1.919998
1.360001
-0.380005
-0.179993
-2.720001
0.029999
0.220001
2.440002
1.679993
3.12001
2.25
1.39
0.119995
-0.589996
3.929992
1.210007
-0.639999
0.479995
0.369996
1
8.690002
-5.62999
2.929993
-2.179993
0.479996
-1
-0.330002
0.979996
1.930008
-1.900009
0.080002
-2.110001
2.139999
1.400009
-0.240005
-1.910004
-2.5
0.320008
1.119995
0.559997
0.040009
-1.020004
-0.949997
-1.660004
2.919998
2.229996
2
-1.12999
-0.36
1.029998
1.149994
-0.690002
1.360001
-0.75
-0.75
-1.37999
1.11
-1.37001
1.880005
-0.809998
-1.479995
-0.970002
-4.740005
1.399994
2.040008
0.89
2.559997
-2.089996
0.529999
-0.650009
1.070007
2.449997
0.300003
-1.050003
0.660004
0.839996
1.040008
0.220002
1.939987
-1.720001
0.570007
-0.300003
-2.899994
-0.400009
-0.519989
2.769989
5.110001
1.310012
1.789994
-1.729996
-1.340012
-0.729995
1.940002
-0.710007
-1.479995
0.040008
-0.850006
0.630005
-1.470001
2.099991
0.540008
-0.430008
0.279999
2.150009
-0.900009
2.160004
0.949997
-1.619996
-5.039993
-0.820007
0.259994
-5.839996
2.050003
3.300003
5.729996
-2.229996
-0.699997
-1.300003
0.98999
0.730011
1.989991
-1.059998
-0.139999
-1.869996
-0.800003
-0.509994
-0.080002
1.399994
0.050003
-0.320007
4.200012
3.019989
0.690002
1.610001
1.5
-1.759995
1.459992
-10.339996
3.440002
-2.240005
-1.12999
2.720001
-0.050003
5.25
3.839996
-1.940002
-0.199997
1
-1.130005
0.75
-0.149994
3.819992
-5.11
-8.359986
5.579987
-3.139999
-6.25
2.300003
-1.440003
-2.169998
7.050003
-1.509995
-3.220001
0.940003
1.98999
1.199997
4.680008
-0.130005
-2.149994
-3.290008
-5.720002
2.910004
5.580002
-3.039994
4.819993
0.350006
1.319992
0.380005
-3.009995
0.639999
1.25
-7.48001
-9.539994
-2.669998
1.330002
-0.690003
-4.619995
-4.510009
-4.660004
3.5
2.660004
-1.259995
-4.520004
9.529999
-3.830002
0.090011
0.109986
7.430008
1.619995
-2.399994
1.139999
0.110001
1.050003
-0.680008
1.589996
-0.519989
-1.840011
-5.289994
13.080002
3.589997
-3.020005
-1.789993
2.25
0.880005
-2.050003
4.270004
0.899994
1.419998
3.479996
1.700012
2.860001
-2.830002
-1.180008
-1.020004
0.810012
0.279999
1.159989
-2.429993
3.380005
0.139999
-1.680008
2.199997
1.330002
5.200012
-1.230011
2.460007
-3.270004
-0.279999
-3.220001
1.279999
3.36
0.570007
0.360001
2.689987
-0.98999
1.440002
2.860001
3.659989
-1.599991
-1.160004
-2.399994
1.579987
-4
2.140014
-3.950012
1.180008
0.190002
3.709992
6.479996
-0.429993
-2.279999
1.209992
4.380005
-0.309998
-2.600006
4.920013
-1.050003
0.080002
1.729996
4.529999
0.61
-40.830002
4.979996
-4.569992
-4.630005
3.259995
-3.25
7.010009
1.279999
7.529999
-1.75
1.100006
-3.810013
-1.939987
0.610001
-1.370011
1.080002
-5.919998
-0.460007
-1.229995
-0.599991
0.879989
0.610001
2.290008
2.110001
-1.800003
-0.400009
1.25
-3.649994
-4.009995
-2.510009
-6.669998
3.199997
0.430007
-0.690002
-1.25
-0.279999
0.199997
-2.529999
0.690003
4.419998
2.139999
-5.61
0.960006
2.309998
3.25
0.779999
-5.300003
-1.449997
-1.580002
1.460007
-2.25
-3.670014
2.150009
-0.869995
-6.690002
6.599991
-3.409989
2.079987
4.160004
-1.050003
-2.649994
-1.100006
-3.539994
3.059998
-6.550003
-1.909989
2.679993
-8.559998
15.059998
-3.479996
0.279999
-1.699997
-0.790008
2.260009
-1.080002
-3.740005
-2.270004
-2.479996
1.699997
-1.369995
-1.259995
-3.460006
-10.580002
7.369995
-0.75
-0.649994
2.75
0.529999
-0.360001
2.339997
4.740005
-2.270004
-6.909989
5.429993
0.350006
4.279999
-0.800003
2.490005
-2.230011
-0.259994
-2
0.130005
-10.51001
2.690002
-10.290001
2.900002
6.440002
2.899994
-0.889999
-5.459992
5.699997
-0.680007
3.550003
2.330001
3.059998
0.130005
0.069992
-1.149994
4.009995
2.990005
-2.050003
2.800003
-0.550003
-0.919998
-3.64
2.839997
0.570007
0.039993
-1.869995
19.380005
0.23999
-0.139999
3.449997
2.050003
-3
-3.729996
3.429993
-1.039993
-1.479996
-2.190003
1.319993
-4.009995
1.75
-0.320007
-1.349991
2.490005
1.269989
-1.440002
-0.529999
0.230011
1.299988
3.470001
5.529999
-1.399994
-5.300003
5.400009
0.48999
0.230011
-2.560012
-2.599991
-3.589997
-2.090011
0.020004
3.389999
0.759995
-2.649994
4.350006
0.5
-3.279999
1.819992
1.440003
2.309997
4.360001
1.520004
0.860001
-1.669998
0.409988
2.559998
0.060012
-0.240005
0.5
0.5
0.600006
-0.800003
-0.550003
4.490005
1.75
12.489991
-4.479996
-1.550003
3.240005
0.589997
-1.779999
1.380005
-3.14
1.299988
-3.149994
-2.190002
1.050003
-4.75
-0.979996
-2.100006
4.630005
-0.210007
-2.959991
2.690002
0.159989
-2.309998
-0.089996
-0.790009
1.960007
-0.419998
-2.800003
];

% make raw data into row vector called FacebookChanges
FacebookChanges = x.';

% make histogram of raw data points (the changes between mornings)
xbins = -15:15;
figure(1)
histogram(FacebookChanges,xbins,'FaceColor','y');
hold on
grid on;

% plot histogram as a line
[yy,xx] = hist(FacebookChanges,xbins);
plot(xx,yy,'k','LineWidth',1);
title('Histogram and Line of Raw Data - FB','FontSize',13);

%% fit Gaussian, Exponential, and Cauchy distributions to data

% set parameters for all 3 distributions
meanStocks = mean(FacebookChanges); % mean of data
variance = var(FacebookChanges); % variance of data
standardDeviation = std(FacebookChanges); % standard deviation of data
maxPoint = max(yy); % max y-value of histogram line (peak)
N=length(FacebookChanges); % length of data set --> 755 data points

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
title('Gaussian Distribution - FB','FontSize',13);
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

pear = find(FacebookChanges > 0);
peach = FacebookChanges(pear); % positive raw data points 
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
title('Exponential Distribution - FB','FontSize',13);
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
title('Cauchy Distribution - FB','FontSize',13);
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
title('Gaussian Prediction - FB');
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
title('Exponential Prediction - FB');
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

meanCauch = mean(stockPriceCauch);
for jj=1:1:length(meanCauch)
    if meanCauch(jj) < 0
        meanCauch(jj) = 0;
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
title('Cauchy Prediction - FB');
grid on

%% predict the stock price average, low, and high on the final day of the time interval
% mean prediction
mC = meanCauch(timeDays+1) + StockStartingPrice;
mE = meanExp(timeDays+1) + StockStartingPrice;
mG = meanGauss(timeDays+1) + StockStartingPrice;

predictionMean = (1/3)*(mC) + (1/3)*(mE) + (1/3)*(mG);

% high prediciton
hC = kiwi(timeDays+1);
hE = percExpHigh(timeDays+1) + meanExp(timeDays+1) + StockStartingPrice;
hG = percGaussHigh(timeDays+1) + meanGauss(timeDays+1) + StockStartingPrice;

predictionHigh = (1/3)*(hC) + (1/3)*(hE) + (1/3)*(hG);

% low prediction
lC = mango(timeDays+1);
lE = percExpLow(timeDays+1) + meanExp(timeDays+1) + StockStartingPrice;
lG = percGaussLow(timeDays+1) + meanGauss(timeDays+1) + StockStartingPrice;

predictionLow = (1/3)*(lC) + (1/3)*(lE) + (1/3)*(lG);

disp(['Facebook Starting Stock Price: ',num2str(StockStartingPrice)]);
disp(['Facebook Average Predicted Stock Price: ',num2str(predictionMean)]);
disp(['Facebook 95th Percentile Predicted Stock Price: ',num2str(predictionHigh)]);
disp(['Facebook 5th Percentile Predicted Stock Price: ',num2str(predictionLow)]);

