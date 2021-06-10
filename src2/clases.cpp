
#include "clases.h"


using namespace std;

ssize_t print_state( FILE *file, const state_t *state )
{
  size_t len, t; int i;
  for( len = 0, i = 0; i < NUMVARS; ++i ) {
    t = fprintf( file, "%s ", var_domain_names[ i ][ state->vars[ i ] ] );
    if( t < 0 ) { return -1; }
    len += t;
  }
  return len;
}

ssize_t read_state( const char *string, state_t *state )
{
  size_t len, t; int i; var_t j;
  len = 0;
  while( (string[len] !=0) && isspace(string[len]) ) { len++; } // skip leading white space
  for( i = 0; i < NUMVARS; ++i ) {
    for( j = 0; j < domain_sizes[ var_domains[ i ] ]; ++j ) {
      t = strlen( var_domain_names[ i ][ j ] );
      if( !strncasecmp( var_domain_names[ i ][ j ], &string[ len ], t ) ) {
          if( (string[len+t] ==0) || isspace(string[len+t]) ) { // require a terminator after the match
	      state->vars[ i ] = j;
	      len += t;
              while( (string[len] !=0) && isspace(string[len]) ) { len++; } // skip the following white space
              break;
          }
      }
    }
    if( j >= domain_sizes[ var_domains[ i ] ] ) { return -1; }
  }
  return len;
}

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

	init_bwd_iter( &iter, &state );
	while ((idRule=next_ruleid(&iter)) >= 0) {
		state_t child;
		State childSt;
		apply_bwd_rule( idRule,&state,&child );
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

