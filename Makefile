GPP = g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = exe

all: $(OBJ)
	$(GPP) -iquote header -o $(EXE) main.cpp $(wildcard *.o)
	rm *.o
	@echo "$(EXE) prêt!"

%.o: %.cpp
	$(GPP) -iquote header -c $<
	

clean:
	rm -f $(EXE) *.o
	@echo "$(EXE) et *.o effacé !"
