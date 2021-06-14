#include <limits>
#include <algorithm>
#include "clases.h"

using namespace std;

const float inf = numeric_limits<float>::infinity();
state_t state;
vector<Action> path;

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

pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g, int history) {
	// base cases
	unsigned h = manhattan(&state);
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
	int  ruleid, child_hist;
	pair<bool,unsigned> p;
	unsigned cost;
	Action a;

	init_fwd_iter( &iter, &state);
	// En par.first esta el estado y en par.second el ruleid de la regla que lo generó 
	while ((ruleid=next_ruleid(&iter)) >= 0) {

		a = ruleid;
		// Poda de padres
		if (!fwd_rule_valid_for_history(history,ruleid)) {
			continue;
		}

		child_hist = next_fwd_history(history,ruleid);
		cost = g + get_fwd_rule_cost(ruleid);

		apply_rule(ruleid, &state);
		print_state(stdout, &state);
		cout << ruleid << "\n";

		if (manhattan(&(state)) < inf) {
			path.push_back(a);
			p = f_bounded_dfs_visit(bound, cost, child_hist);

			if (p.first == true) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back();
		}

		revert_rule(a, &state);
	}
}

void ida_search() {
	unsigned bound = manhattan(&state);
	int hist = init_history;
	// Search with increasing f-value bounds
	while (true) {

		pair<bool,unsigned> p = f_bounded_dfs_visit(bound, 0, hist);

		if (p.first == true) {
			break;
		}

		bound = p.second;
	}
}

int main() {
	char str[MAX_LINE_LENGTH + 1] = "1 3 2 b"; // Para la prueba se pone una representación del estado en string
	ssize_t nchars = read_state(str, &state); // Esto convierte el str a un estado de psvn

	cout << manhattan(&state) << endl;

	ida_search();
}