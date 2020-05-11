function nextQuestion=findBestPath(crntArray)
% This function will find the question with the most varied answers to give
% the path of best efficiency.
[n,m]=size(crntArray);
bestVariance=n/2;
sumAnswers=zeros(1,m);
for icol=1:m
    sumAnswers(icol)=sum(crntArray(:,icol));
end
difference=zeros(1,m);
for icol=1:m
    difference(icol)=abs(bestVariance-sumAnswers(icol));
end
minPos=1;
while difference(minPos)~=min(difference);
        minPos=minPos+1;
end
nextQuestion=minPos;
