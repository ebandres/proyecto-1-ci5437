#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

using namespace std;
using namespace std::chrono;


state_t *state;
unsigned mtable[16][16];
vector<int> path;


// Genera un sucesor del estado 
void apply_rule(int ruleid, state_t *state) {
	// No se puede sobreescribir un estado directamente :) y hay que pasar el
	// state como apuntador para que si se guarden los cambios
	state_t state_aux;
	copy_state(&state_aux, state);
	apply_fwd_rule(ruleid, &state_aux, state);
	//print_state(stdout, state);
}

// Generar el padre del estado
void revert_rule(int ruleid, state_t *state) {
	state_t state_aux;
	copy_state(&state_aux, state);
	apply_bwd_rule(ruleid, &state_aux, state);
}


unsigned manhattan(state_t *state) { 
  	char st[100];
  	sprint_state(st, 100, state);
  	char *token, *rest = st;
  	int val, index = 0;
  	int h = 0;

	while ((token = strtok_r(rest, " ", &rest))) {
		if (strcmp(token, "b") == 0)  {
			index++;
			continue;
		}

    	val = atoi(token);

    	h += abs(index / 4 - val / 4) + abs(index % 4 - val % 4);
    	index++;
	}
	return h; 
}

void setManhattan(){
	unsigned prov[16][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						   {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
						   {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
						   {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
						   {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
						   {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
						   {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
						   {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
						   {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
						   {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
						   {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
						   {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
						   {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
						   {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
						   {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
						   {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}};

	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			mtable[i][j] = prov[i][j];
		}
	}
}

unsigned manhattan2(state_t puzzle_state){
   unsigned h=0;
   for (int i=0; i<=15; i++){
      h += mtable[puzzle_state.vars[i]][i];
   }
   return h;
}

pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g,bool pruning, int history) {
	// base cases
	//unsigned h = manhattan(state);
	unsigned h = heuristic(*state);
	unsigned f = g + h;

	if (f > bound) {
		return {false,f};
	}

	if (h == 0) {
		return {true,f};
	}

	unsigned t = UINT_MAX;

	// Variables para generar los sucesores
	ruleid_iterator_t iter;
	int  ruleid, child_hist;
	pair<bool,unsigned> p;
	unsigned cost;

	init_fwd_iter( &iter, state);
	// En par.first esta el estado y en par.second el ruleid de la regla que lo generó 
	while ((ruleid=next_ruleid(&iter)) >= 0) {

	    if (pruning) {
	      if (! fwd_rule_valid_for_history(history, ruleid)) continue;
	      child_hist = next_fwd_history(history, ruleid);
	    } else {
	      child_hist = 0;
	    }

		cost = g + get_fwd_rule_cost(ruleid);

		apply_rule(ruleid, state);
		//print_state(stdout, state);
		//cout << "rule " << ruleid << endl;

		//if (manhattan(state) < UINT_MAX) {
		if (heuristic(*state) < UINT_MAX) {
			path.push_back(ruleid);
			p = f_bounded_dfs_visit(bound, cost, pruning, child_hist);

			if (p.first) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back();
		}

		revert_rule(ruleid, state);
	}
	return {false,t};
}

vector<int> ida_search(state_t *init, bool pruning) {
	state = init;
	//unsigned bound = manhattan(state);
	unsigned bound = heuristic(*state);
	pair<bool,unsigned> p;
	int hist = init_history;
	// Search with increasing f-value bounds
	while (bound != UINT_MAX) {

		p = f_bounded_dfs_visit(bound, 0, pruning, hist);

		if (p.first) {
			return path;
		}

		bound = p.second;
	}
	path.clear();
	return path;
}

int main() {
  vector<int> result;
  state_t *init;
  char str[100 + 1] = "14 1 9 6 4 8 12 5 7 2 3 B 10 11 13 15"; // Para la prueba se pone una representación del estado en string
  //char str[100 + 1] = "B 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"; 
  ssize_t nchars = read_state(str, init); // Esto convierte el str a un estado de psvn
  //setManhattan();
  establishHeuristic();
  auto start = high_resolution_clock::now();

  result = ida_search(init,true);
  //unsigned test = heuristic(*init);
  //cout << "HEURISTIC VALUE: " << test << endl;
  auto stop = high_resolution_clock::now();
  duration<double> total = stop - start;
  cout << "time: " << total.count() << " segundos" << endl;
}