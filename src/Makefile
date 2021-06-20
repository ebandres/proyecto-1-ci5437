CC = g++

all: main

ida.o:
	$(CC) -c ida.cpp -include 15puzzle.c

main.o: ida.o
	$(CC) -c main.cpp -include 15puzzle.c -include heuristicas.cpp

main: main.o
	$(CC) -o main main.o ida.o

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CC) $(OPT) abstractor.cpp psvn.cpp -o $@

%.distSummary: %.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) distSummary.cpp -include $< -o $@