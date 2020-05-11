function possibleBirds=eliminateWrongBirds(crntArray,question,answer)
[n,m]=size(crntArray);
newRowCnt=1;
possibleBirds=zeros(1,60);
for irow=1:n
    if crntArray(irow,question)==answer
        possibleBirds(newRowCnt,:)=crntArray(irow,:);
        newRowCnt=newRowCnt+1;
    end
end