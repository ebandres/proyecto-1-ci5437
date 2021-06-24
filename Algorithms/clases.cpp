
#include "clases.h"


using namespace std;


bool State::isGoalState() {
	if ((is_goal(&state)) == 1) {
		return true;
	} else {
		return false;
	}
}

list<pair<State,int>> State::succesors() {
	int idRule;
	list<pair<State,int>> listPair;
	init_fwd_iter( &iter, &state );

	while ((idRule=next_ruleid(&iter)) >= 0) {

		state_t child;
		State childSt;
		apply_fwd_rule( idRule,&state,&child );
		//print_state(stdout, &child);
		childSt.state = child;
		childSt.ruleid = idRule;
		listPair.push_back(make_pair(childSt,idRule));
	}

	return listPair;
}

Node::Node(state_t state1, Node* parent1, int ruleid1, unsigned g1) {
	state = state1;
	parent = parent1;
	ruleid = ruleid1;
	g = g1;
}

Node* Node::make_node(state_t state, Node* parent, int ruleid) {
	return new Node(state,parent,ruleid,parent->g + get_fwd_rule_cost(state.ruleid));
}

void Node::extract_path(vector<int> &reversed_path, Node nodito) {
	Node node = nodito;
	while (&(node) != NULL && node.parent != NULL) {
		reversed_path.push_back(node.ruleid);
		node = *(node.parent);
	}
}


Node make_root_node(state_t state) {
	return Node(state, NULL, -1, 0);
}

