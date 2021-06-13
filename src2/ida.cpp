#include <limits>
#include <algorithm>
#include "clases.h"

using namespace std;

const float inf = numeric_limits<float>::infinity();
state_t state;
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
	unsigned h = manhattan(&(state));
	unsigned f = g + h;

	if (f > bound) {
		return make_pair(false,f);
	}

	if (h == 0) {
		return make_pair(true,g);
	}

	unsigned t = numeric_limits<unsigned>::infinity();

	// Variables para generar los sucesores
	ruleid_iterator_t iter;
	int  ruleid, hist, child_hist;
	Action a;
	hist = init_history;


	init_fwd_iter( &iter, &state);
	// En par.first esta el estado y en par.second el ruleid de la regla que lo generó 
	while ((ruleid=next_ruleid(&iter)) >= 0) {

		a = ruleid;
		// Poda de padres
		if (!fwd_rule_valid_for_history(hist,ruleid)) {
			continue;
		}

		child_hist = next_fwd_history(hist,ruleid);
		unsigned cost = g + get_fwd_rule_cost(ruleid);
		apply_fwd_rule(ruleid,&state,&state);

		if (manhattan(&(state)) < inf) {
			path.push_back(a);
			pair<bool,unsigned> p = f_bounded_dfs_visit(bound, cost);

			if (p.first == true) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back();
		}

		apply_bwd_rule(a, &state, &state);
	}
}

void ida_search(state_t init) {
	state = init;
	unsigned bound = manhattan(&state);
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
	ssize_t nchars = read_state(str, &state); // Esto convierte el str a un estado de psvn

	cout << manhattan(&state) << endl;
}