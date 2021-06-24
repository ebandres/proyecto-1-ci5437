CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --fwd_history_len=1
FLAG = -c

all: 15puzzle 24puzzle topspin12 topspin14 topspin17 hanoi12 hanoi14 hanoi18
	rm -f 15puzzle.c 24puzzle.c topspin_12_4.c topspin_14_4.c topspin_17_4.c hanoi_4p12d.c hanoi_4p14d.c hanoi_4p18d.c iddfs.o clases.cpp clases.h clases.o

15puzzle: clases.h 15puzzle.c
	$(CXX) -c clases.cpp -include 15puzzle.c
	$(CXX) -c iddfs.cpp -include 15puzzle.c
	$(CXX) -o iddfs_15p iddfs.o clases.o

24puzzle: clases.h 24puzzle.c
	$(CXX) -c clases.cpp -include 24puzzle.c
	$(CXX) -c iddfs.cpp -include 24puzzle.c
	$(CXX) -o iddfs_24p iddfs.o clases.o

topspin12: clases.h topspin_12_4.c
	$(CXX) -c clases.cpp -include topspin_12_4.c
	$(CXX) -c iddfs.cpp -include topspin_12_4.c
	$(CXX) -o iddfs_top12 iddfs.o clases.o

topspin14: clases.h topspin_14_4.c
	$(CXX) -c clases.cpp -include topspin_14_4.c
	$(CXX) -c iddfs.cpp -include topspin_14_4.c
	$(CXX) -o iddfs_top14 iddfs.o clases.o

topspin17: clases.h topspin_17_4.c
	$(CXX) -c clases.cpp -include topspin_17_4.c
	$(CXX) -c iddfs.cpp -include topspin_17_4.c
	$(CXX) -o iddfs_top17 iddfs.o clases.o

hanoi12: clases.h hanoi_4p12d.c
	$(CXX) -c clases.cpp -include hanoi_4p12d.c
	$(CXX) -c iddfs.cpp -include hanoi_4p12d.c
	$(CXX) -o iddfs_hanoi12 iddfs.o clases.o

hanoi14: clases.h hanoi_4p14d.c
	$(CXX) -c clases.cpp -include hanoi_4p14d.c
	$(CXX) -c iddfs.cpp -include hanoi_4p14d.c
	$(CXX) -o iddfs_hanoi14 iddfs.o clases.o

hanoi18: clases.h hanoi_4p18d.c
	$(CXX) -c clases.cpp -include hanoi_4p18d.c
	$(CXX) -c iddfs.cpp -include hanoi_4p18d.c
	$(CXX) -o iddfs_hanoi18 iddfs.o clases.o

clases.h:
	cp ../Algorithms/clases.h ./clases.h
	cp ../Algorithms/clases.cpp ./clases.cpp

15puzzle.c:
	cp ../Problems/NPuzzle/15Puzzle/15puzzle.c ./15puzzle.c

24puzzle.c:
	cp ../Problems/NPuzzle/24Puzzle/24puzzle.c ./24puzzle.c

topspin_12_4.c:
	cp ../Problems/TopSpin/TopSpin_12_4/topspin_12_4.c ./topspin_12_4.c

topspin_14_4.c:
	cp ../Problems/TopSpin/TopSpin_14_4/topspin_14_4.c ./topspin_14_4.c

topspin_17_4.c:
	cp ../Problems/TopSpin/TopSpin_17_4/topspin_17_4.c ./topspin_17_4.c

hanoi_4p12d.c:
	cp ../Problems/TowersOfHanoi/Hanoi4p12d/hanoi_4p12d.c ./hanoi_4p12d.c

hanoi_4p14d.c:
	cp ../Problems/TowersOfHanoi/Hanoi4p14d/hanoi_4p14d.c ./hanoi_4p14d.c

hanoi_4p18d.c:
	cp ../Problems/TowersOfHanoi/Hanoi4p18d/hanoi_4p18d.c ./hanoi_4p18d.c