#include <limits>
#include <algorithm>
#include "clases.h"

using namespace std;

const float inf = numeric_limits<float>::infinity();
State state;
vector<Action> path;

unsigned manhattan(state_t *state) { 
  	char st[100];
  	sprint_state(st, 100, state);
  	char *token, *rest = st;
  	int val, index = 0;
  	unsigned h = 0;

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

pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g) {
	// base cases
	unsigned h = manhattan(&(state.state));
	unsigned f = g + h;

	if (f > bound) {
		return make_pair(false,f);
	}

	if (h == 0) {
		return make_pair(true,g);
	}

	unsigned t = numeric_limits<unsigned>::infinity();

	// En par.first esta el estado y en par.second el ruleid de la regla que lo generó 
	for (auto const& par : state.succesors()) {

		unsigned cost = g + get_fwd_rule_cost(par.second);
		state = par.first;

		if (manhattan(&(state.state)) < inf) {
			path.push_back(par.second);
			pair<bool,unsigned> p = f_bounded_dfs_visit(bound, cost);

			if (p.first == true) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back();
		}

		apply_bwd_rule(par.second, &(state.state), &(state.state));
	}
}

void ida_search(State init) {
	state = init;
	unsigned bound = manhattan(&(init.state));
	// Search with increasing f-value bounds
	while (true) {

		pair<bool,unsigned> p = f_bounded_dfs_visit(bound, 0);

		if (p.first == true) {
			break;
		}

		bound = p.second;
	}
}



int main() {
	char str[MAX_LINE_LENGTH + 1] = "1 2 3 b"; // Para la prueba se pone una representación del estado en string
	state_t stateTest;
	ssize_t nchars = read_state(str, &stateTest); // Esto convierte el str a un estado de psvn
	state.state = stateTest;

	cout << manhattan(&(state.state)) << endl;
}