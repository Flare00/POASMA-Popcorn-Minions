main: grid agent case
	g++ main.cpp grid.o case.o agent.o -o exec
grid:
	g++ grid.cpp -c
agent:
	g++ agent.cpp -c
case:
	g++ case.cpp -c