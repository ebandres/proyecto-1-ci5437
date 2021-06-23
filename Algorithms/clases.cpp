
#include "clases.h"


using namespace std;


typedef unsigned Action;

bool State::isGoalState() {
	if ((is_goal(&state)) == 1) {
		return true;
	} else {
		return false;
	}
}

list<pair<State,Action>> State::succesors() {
	int idRule;
	list<pair<State,Action>> listPair;
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

	Node::Node(State state1, Node* parent1, Action action1, unsigned g1) {
		state = state1;
		parent = parent1;
		action = action1;
		g = g1;
	}

	Node* Node::make_node(State state, Node* parent, Action action) {
		return new Node(state,parent,action,parent->g + get_fwd_rule_cost(state.ruleid));
	}

	void Node::extract_path(vector<Action> &reversed_path, Node nodito) {
	Node node = nodito;
	while (&(node) != NULL && node.parent != NULL) {
		reversed_path.push_back(node.action);
		node = *(node.parent);
	}
}


Node make_root_node(State state) {
	return Node(state, NULL, -1, 0);
}

