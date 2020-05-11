# Molly Doyle
# Fundamentals of Computing - Lab 13 Final Project 
# Make file 

CMP = g++ -std=c++0x
CLASS = brickbreaker
MAIN = project
EXEC = project 

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o gfx.o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp gfx.o -lX11 -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp gfx.o -lX11 -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)
