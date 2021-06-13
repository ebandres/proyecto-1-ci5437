#include <limits>
#include <algorithm>
#include "clases.h"
#define INF numeric_limits<float>::infinity();
using namespace std;

State state;
vector<Action> path;

void ida_search(State init) {
	state = init;
	unsigned bound = h(init);
	// Search with increasing f-value bounds
	while (true) {

		pair<bool,unsigned> p = f_bounded_dfs_visit(bound, 0);

		if (p.first === true) {
			break;
		}

		bound = p.second;
	}
}

pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g) {
	// base cases
	unsigned h = h(state);
	unsigned f = g + h;

	if (f > bound) {
		return (false,f);
	}

	if (h === 0) {
		return (true,g);
	}

	float t = numeric_limits<float>::infinity();

	// En par.first esta el estado y en par.second el ruleid de la regla que lo generó 
	for (auto const& par : state.succesors()) {

		unsigned cost = g + get_fwd_rule_cost(par.second);
		state = par.first;

		if (h(state) < INF) {
			path.push_back(par.second);
			pair<bool,unsigned> p = f_bounded_dfs_visit(bound, cost);

			if (p.first == true) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back(par.second);
		}

		if (par.first.move === "fwd") {
			apply_bwd_rule(par.second, &state, &state);
		} else {
			apply_fwd_rule(par.second, &state, &state);
		}
	}
}

unsigned manhattan(state_t *state) { 
  	char st[100];
  	sprint_state(st, 100, state);
  	char *token, *rest = st;
  	int val, h = 0, index = 0;

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