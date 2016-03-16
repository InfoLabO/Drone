CC   = g++
LIB  = -lsfml-window -lsfml-graphics -lsfml-system -lGL -lboost_system
FLAG = -Wall
SRC  = main.cpp
EXE  = droneSimulator

all :
	$(CC) $(SRC) -o $(EXE) $(LIB) $(INCLDIR) $(LIBSDIR) $(FLAG)

clean :
	rm -rf *~

cleanall : clean
	rm -rf $(EXE)
