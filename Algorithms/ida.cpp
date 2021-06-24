// El archivo se llama ida pero también contiene A*
#include "ida.h"

using namespace std;
using namespace std::chrono;

//Variables globales
state_t *state;
vector<int> path;
time_point<high_resolution_clock> start_time;
double time_limit = 900;

// Genera un sucesor del estado 
void get_next(int ruleid, state_t *state) {
	// No se puede sobreescribir un estado directamente :) y hay que pasar el
	// state como apuntador para que si se guarden los cambios
	state_t state_aux;
	copy_state(&state_aux, state);
	apply_fwd_rule(ruleid, &state_aux, state);
}

// Generar el padre del estado
void get_prev(int ruleid, state_t *state) {
	state_t state_aux;
	copy_state(&state_aux, state);
	apply_bwd_rule(ruleid, &state_aux, state);
}

// Código recursivo del IDA*
pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g,unsigned (*heuristic) (state_t),bool pruning, int history, int64_t &generatedNodes) {
	// Check time limit
	auto curr_time = high_resolution_clock::now();
	duration<double> elapsed = curr_time - start_time;
	if (elapsed.count() > time_limit)
	{
		throw 3;
	}
	
	// casos base
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

	generatedNodes += 1;

	// Inicializando el iterador
	init_fwd_iter( &iter, state);
	// Iterando sobre los sucesores
	while ((ruleid=next_ruleid(&iter)) >= 0) {

	    if (pruning) {
	    	if (! fwd_rule_valid_for_history(history, ruleid)) continue;
	    	child_hist = next_fwd_history(history, ruleid);
	    } else {
	    	child_hist = 0;
	    }

		cost = g + get_fwd_rule_cost(ruleid);

		get_next(ruleid, state);

		if (heuristic(*state) < UINT_MAX) {
			path.push_back(ruleid);
			p = f_bounded_dfs_visit(bound, cost, heuristic, pruning, child_hist, generatedNodes);

			if (p.first) {
				return p;
			}

			t = min(t,p.second);
			path.pop_back();
		}

		get_prev(ruleid, state);
	}
	return {false,t};
}

vector<int> ida_search(state_t *init,unsigned (*heuristic) (state_t), bool pruning, int64_t &generatedNodes, time_point<high_resolution_clock> st) {
	path.clear();
	start_time = st;
	generatedNodes = 1;
	state = init;
	unsigned bound = heuristic(*state);
	pair<bool,unsigned> p;
	int hist = init_history;
	
	while (bound != UINT_MAX) {

		p = f_bounded_dfs_visit(bound, 0,heuristic, pruning, hist, generatedNodes);

		if (p.first) {
			return path;
		}

		bound = p.second;
	}
	path.clear();
	return path;
}

///////////// A STAR

int a_search(state_t *init, unsigned (*heuristic) (state_t), bool pruning, int64_t &generatedNodes, time_point<high_resolution_clock> st) {
	path.clear();
	start_time = st;
	generatedNodes = 1;

	time_point<high_resolution_clock> curr_time;
	
	PriorityQueue<state_t> q;
	state_t curr_state;
	state_t child_state;
	int curr_g;
    int *prev_g;
    int child_h;
    int child_g;
    int ruleid;
    ruleid_iterator_t iter;
	state_map_t *costs = new_state_map();

	state_map_add(costs, init, 0);
	q.Add(0, 0, *init);

	while (!q.Empty()) {
		curr_state = q.Top();
		curr_g = q.CurrentPriority();
		q.Pop();

		curr_time = high_resolution_clock::now();
		duration<double> elapsed = curr_time - start_time;
		if (elapsed.count() > time_limit)
		{
			throw 3;
		}

		prev_g = state_map_get(costs, &curr_state);

		if (prev_g == NULL || !compare_states(&curr_state, init) || curr_g < *prev_g) {
			//Actualizar los costos si se consiguió alguno menor para un estado previamente encontrado, 
			// o añadir un estado nuevo con su respectivo costo
			state_map_add(costs, &curr_state, curr_g);

			if (is_goal(&curr_state)) {
				return curr_g;
			}

			generatedNodes++;

			init_fwd_iter(&iter, &curr_state);
			while ((ruleid = next_ruleid(&iter)) >= 0) {
				apply_fwd_rule(ruleid, &curr_state, &child_state);
				child_h = heuristic(child_state);

				if (child_h < INT_MAX) {
					child_g = curr_g + get_fwd_rule_cost(ruleid);
					q.Add(child_g + child_h, child_g, child_state);
				}
			}
		}
	}
	return -1;
}

