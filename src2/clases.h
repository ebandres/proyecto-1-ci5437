#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <string>
#include <list>
#include <vector>
#include <cstddef>
#define  MAX_LINE_LENGTH 999
using namespace std;

typedef unsigned Action;

class State {
	public:
	state_t state;
	ruleid_iterator_t iter;
	int  ruleid;
	string move;

	bool isGoalState();
	list<pair<State,Action>> succesors();
};

// Object Node
class Node {
	public:
		State state;
		Node* parent;
		Action action;
		unsigned g;

		Node(State state1, Node* parent1, Action action1, unsigned g1);

		Node* make_node(State state, Node* parent, Action action);

		void extract_path(vector<Action> &reversed_path, Node nodito);
};

Node make_root_node(State state);