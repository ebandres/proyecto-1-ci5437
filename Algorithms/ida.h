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

//state_t *state;
//vector<int> path;
//unsigned (*heuristic) (state_t);

void apply_rule(int ruleid, state_t *state);
void revert_rule(int ruleid, state_t *state);
pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g,unsigned (*heuristic) (state_t),bool pruning, int history, int64_t &generatedNodes);
vector<int> ida_search(state_t *init, unsigned (*heuristic) (state_t), bool pruning, int64_t &generatedNodes, time_point<high_resolution_clock> st);

