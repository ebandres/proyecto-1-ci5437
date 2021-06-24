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


class State {
	public:
	state_t state;
	ruleid_iterator_t iter;
	int  ruleid;

	bool isGoalState();
	list<pair<State,int>> succesors();
};

// Object Node
class Node {
	public:
		state_t state;
		Node* parent;
		int ruleid;
		unsigned g;

		Node(state_t state1, Node* parent1, int ruleid1, unsigned g1);

		Node* make_node(state_t state, Node* parent, int ruleid);

		void extract_path(vector<int> &reversed_path, Node nodito);
};

Node make_root_node(state_t state);