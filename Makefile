GPP = g++
SRC = agent.cpp batiment.cpp case.cpp main.cpp
OBJ = $(SRC:%.cc=%.o)
EXE = exe

all: $(OBJ)
	$(GPP) -o $(EXE) $(OBJ)
	rm -f *~ *.o
	@echo "$(EXE) prêt!"

%.o: %.cpp
	$(GPP) -c $<

clean:
	rm -f $(EXE)
	@echo "$(EXE) effacé !"