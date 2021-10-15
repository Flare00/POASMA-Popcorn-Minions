GPP = g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = exe

all: $(OBJ)
	$(GPP) -iquote header -g -o $(EXE) main.cpp $(OBJ) -L/usr/lib -lglut -lGLU -lGL -lm -lpthread -lgsl -lgslcblas
	rm src/*.o
	@echo "$(EXE) prêt!"


%.o: %.cpp
	$(GPP) -iquote header -g -c $< -o $@
	

clean:
	rm -f $(EXE) src/*.o
	@echo "$(EXE) et *.o effacé !"
