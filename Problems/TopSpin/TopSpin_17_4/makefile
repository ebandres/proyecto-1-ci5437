# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --fwd_history_len=1
FLAG = -c

psvn2c_core.c:
	cp ../../../psvn/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../../psvn/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../../psvn/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../../psvn/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../../../psvn/global/succ.c
	$(CC) $(OPT) ../../../psvn/global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../../psvn/global/dist.cpp
	$(CXX) $(OPT) ../../../psvn/global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../../psvn/global/distSummary.cpp
	$(CXX) $(OPT) ../../../psvn/global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	$(CXX) $(OPT) ../../../psvn/src/abstractor.cpp ../../../psvn/src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor `dirname $*`.psvn `basename $*` < `basename $*`.txt > /dev/null
	@make `basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`basename $*`.distSummary `basename $*`.pdb
	@rm -f abstractor `basename $*`.distSummary

%.dist_pdb: %.c ../../../psvn/global/dist_pdb.cpp
	$(CXX) $(OPT) ../../../psvn/global/dist_pdb.cpp -include $< -o $@
	rm -f $*.c

main: ida.o main.o
	$(CXX) -o main ida.o main.o
	rm -f ida.o main.o ida.h ida.cpp priority_queue.hpp clases.cpp clases.h

priority_queue.hpp:
	cp ../../../Algorithms/priority_queue.hpp ./priority_queue.hpp

clases.cpp:
	cp ../../../Algorithms/clases.cpp ./clases.cpp
	cp ../../../Algorithms/clases.h ./clases.h

ida.o: ida.cpp priority_queue.hpp clases.cpp
	$(CXX) -c ida.cpp -include topspin_17_4.c

main.o: main.cpp ida.h
	$(CXX) -c main.cpp -include topspin_17_4.c -include heuristicas.cpp

ida.cpp: 
	cp  ../../../Algorithms/ida.cpp ./ida.cpp
	cp  ../../../Algorithms/ida.h ./ida.h





.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
