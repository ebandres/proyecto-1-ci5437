#include <limits>
#include <algorithm>
#include "clases.h"

using namespace std;

// Implementación de IDA*
Node ida_search(State init) {

	Node root = make_root_node(init);
	unsigned bound = h(init);

	while true {

		pair<Node, unsigned> p = f_bounded_dfs_visit(root, bound);
		if (p.first != NULL) {
			return p.first;
		}
	bound = p.second;
	}
}

pair<Node, unsigned> f_bounded_dfs_visit(Node n, unsigned bound) {
	unsigned f = n.g + h(n.state);

	if (f > bound) {
		return (NULL, f);
	}

	if (n.state.isGoalState()) {
		return (n,n.g);
	}

	float t = numeric_limits<float>::infinity();
	list<pair<State,Action>> listaPar = n.state.succesors();

	for (auto const& par : listaPar) {
		Node* m = n.make_node(par.first, &n, par.second);
		pair<Node, unsigned> p = f_bounded_dfs_visit(*m, bound);

		if (p.first != NULL) {
			return p;
		}

		t = min(t,p.second);
	}
	return (NULL,t);
}