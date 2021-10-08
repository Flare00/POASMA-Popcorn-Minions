GPP = g++
SRC = agent.cpp batiment.cpp case.cpp fire.cpp minion.cpp main.cpp
OBJ = $(./src/SRC:%.cpp=%.o)
EXE = exe

all: $(OBJ)
	$(GPP) -o $(EXE) $(OBJ)
	rm *.o
	@echo "$(EXE) prêt!"

%.o: %.cpp
	$(GPP) -c $<

clean:
	rm -f $(EXE)
	@echo "$(EXE) effacé !"
