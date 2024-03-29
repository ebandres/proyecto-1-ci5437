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
#include "priority_queue.hpp"

using namespace std;
using namespace std::chrono;

void get_next(int ruleid, state_t *state);

void get_prev(int ruleid, state_t *state);

pair<bool,unsigned> f_bounded_dfs_visit(unsigned bound, unsigned g,unsigned (*heuristic) (state_t),bool pruning, int history, int64_t &generatedNodes);

vector<int> ida_search(state_t *init, unsigned (*heuristic) (state_t), bool pruning, int64_t &generatedNodes, time_point<high_resolution_clock> st);

int a_search(state_t *init, unsigned (*heuristic) (state_t), bool pruning, int64_t &generatedNodes, time_point<high_resolution_clock> st);
