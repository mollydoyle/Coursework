function RowArray=col2rowsampF
%This program will run through the first 10 sample of birds to convert the
%column bit vector of characteristics to row vectors. 
%Author: Group 11, Bird Identifier 


%% Import data of column vectors
ColArray=OrganizingBinaryMatrixF();

%% Use for loop to convert each column vector into a row vector
RowArray=zeros(293,60);
for icol=1:293
    RowArray(icol,:)=ColArray(:,icol)';
end
