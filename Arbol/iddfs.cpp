#include <vector>
#include <stdbool.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <signal.h>
#include "clases.h"

using namespace std;
using namespace std::chrono;

vector<int64_t> num_states;
ofstream results;
time_point<high_resolution_clock> start_time;
double time_limit = 900;

void signal_callback_handler(int signum) {

	if (results.is_open())
	{
		results << "\nProgram terminated by user" << endl;
		results.close();
	}
	
	exit(signum);
}

void bounded_dfs_visit(Node *node, unsigned depth, unsigned bound, const int history) {
    auto curr_time = high_resolution_clock::now();
	duration<double> elapsed = curr_time - start_time;
	if (elapsed.count() > time_limit)
	{
		throw 3;
	}

    ruleid_iterator_t iter;
    state_t child_state;
    int ruleid;

    if (depth <= bound) {  
        if (num_states.size() < depth + 2) {
            num_states.push_back(1);
        }
        else if (depth==bound) {
            num_states[depth + 1] += 1;
        }

        init_fwd_iter(&iter, &(node->state));

        while((ruleid = next_ruleid(&iter)) >= 0) {
            if( fwd_rule_valid_for_history(history, ruleid) == 0){
                continue; 
            }
            apply_fwd_rule(ruleid, &(node->state), &child_state);

            Node child_node(child_state, node, ruleid, 0); 

            int new_history = next_fwd_history(history, ruleid);
            bounded_dfs_visit(&child_node, depth + 1, bound, new_history);  
        }
    }
}

void iterative_deepening_dfs(state_t *root_state) {   
    unsigned bound = 1; 
    double ramificacion; 
    num_states.assign(1,1);

    Node root_node = make_root_node(*root_state);

    bounded_dfs_visit(&root_node, 0, 0, init_history);

    while (1) {
        bounded_dfs_visit(&root_node, 0, bound, init_history);
        ramificacion = static_cast<float>(num_states[bound + 1])/ num_states[bound];
        cout << bound - 1 << "\t" << num_states[bound] << "\t" << ramificacion << endl;
        results << bound - 1 << "\t" << num_states[bound] << "\t" << ramificacion << endl;
        bound += 1;
    }
}

int main(int argc, char** argv) {
	signal(SIGINT, signal_callback_handler);

    state_t goal_state;
    int d;
    first_goal_state(&goal_state, &d);

    string filename(argv[0]);
    filename = "results_" + filename + ".txt";
	results.open(filename, ios::out | ios::trunc);

    results << "Depth\tNum Nodes\tBranching" << endl;

    start_time = high_resolution_clock::now();

    try
    {
        iterative_deepening_dfs(&goal_state);
    }
    catch(int e)
    {
        if (e == 3)
		{
			cout << "Time limit reached" << endl;
			results << "Time limit reached" << endl;
		}
		else
		{
			cout << "Error code " << e << endl;
			results << "Error code " << e << endl;
		}
    }
    
    results.close();

    return 0;
}

