%% BirdCompleteProgram.m
% This is the complete program for the twenty questions game that will
% guess the bird that a user is thinking of from ___ birds. 
% Author: Group 11, Section 02

%% Load in the names of the possible birds
birdslist=namesofbirdsF;
%% Use function with total questions, bird identifications, and randomizer for first question to start game
questions=QuestionsArrayF; %This imports a cell array with all of the total characteristics
birds=col2rowsampF;  %This starts out including all of the characteristics of each bird 
[a,b]=size(birds);  
guessbird=false;  %This is a logical variable showing whether or not the computer is ready to guess the bird
for iquestion=1:length(questions)
    firstquestion=questions(iquestion); %This allows the program to run starting with each question once
    disp(firstquestion);
    answer=input(' ');
    positionQuestion=iquestion;
    qstnCnt=ones(60);
    crntArray=birds;  %This makes a copy of the total birds array to use for the elimination function without changing the initial birds array
    while ~guessbird
        possibleBirds=eliminateWrongBirds(crntArray,positionQuestion,answer);
        nextQuestion=findBestPath(possibleBirds);
        [n,m]=size(possibleBirds);
        if n==1
            guessbird=true;
        else
            qstnCnt(iquestion)=qstnCnt(iquestion)+1;
            positionQuestion=nextQuestion;
            Askquestion=questions((nextQuestion));
            disp(Askquestion);
            answer=input(' ');
            crntArray=possibleBirds;
        end
    end 
    for ibird=1:a
        if possibleBirds==birds(ibird,:)
            correctbird=birdslist(ibird);
        end
    end
            disp(['Your bird is',correctbird,'!']);
            guessbird=false;
end
    