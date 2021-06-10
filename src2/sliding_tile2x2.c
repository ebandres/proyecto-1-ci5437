#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING
#define HAVE_BWD_MOVES
#define HAVE_BWD_MOVE_PRUNING
#define HAVE_ABSTRACTION


/* number of variables in a state */
#define NUMVARS 4


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 4 };
static const char *name_of_domain[ NUMDOMAINS ] = { "TILE" };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0 };
static const char *domain_0[ 4 ] = {"B", "1", "2", "3" };
static const char **domain_to_domain_names[ NUMDOMAINS ] = { domain_0 };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 4
#define num_bwd_rules 4
static const char *fwd_rule_name[ 4 ] = { "rule_1", "rule_2", "rule_3", "rule_4" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
static const char *bwd_rule_name[ 4 ] = { "rule_1", "rule_2", "rule_3", "rule_4" };
#define get_bwd_rule_label( ruleid ) (bwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 1
#define get_fwd_rule_cost( ruleid ) 1
#define cost_of_cheapest_bwd_rule 1
#define cost_of_costliest_bwd_rule 1
#define get_bwd_rule_cost( ruleid ) 1

static int fwd_rule_label_sets[16] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

static int bwd_rule_label_sets[16] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

static int fwd_prune_table[ 20 ] = { 4, 8, 12, 16, 0, 0, 12, 16, 0, 0, 12, 16, 4, 0, 0, 0, 0, 8, 0, 0 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 2 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 3 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 0;
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = 0;
}

static actfuncptr fwd_rules[ 4 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4 };

static int fwdfn2_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 1;
}

static int fwdfn2( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn2_a0_1;
    return 0;
  } else {
    return -1;
  }
}

static int fwdfn1( const state_t *state, void *next_func )
{
  if( state->vars[ 2 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn2;
    return 3;
  } else {
    return fwdfn2( state, next_func );
  }
}

static int fwdfn0( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn1;
    return 2;
  } else {
    return fwdfn1( state, next_func );
  }
}

static int bwd_prune_table[ 20 ] = { 4, 8, 12, 16, 0, 0, 12, 16, 0, 0, 12, 16, 4, 0, 0, 0, 0, 8, 0, 0 };

static void bwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
}

static void bwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 0 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
}

static void bwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 1 ];
}

static void bwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 2 ];
}

static actfuncptr bwd_rules[ 4 ] = { bwdrule1, bwdrule2, bwdrule3, bwdrule4 };

static int bwdfn2_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 3;
}

static int bwdfn2( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn2_a0_1;
    return 2;
  } else {
    return -1;
  }
}

static int bwdfn1( const state_t *state, void *next_func )
{
  if( state->vars[ 2 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn2;
    return 1;
  } else {
    return bwdfn2( state, next_func );
  }
}

static int bwdfn0( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn1;
    return 0;
  } else {
    return bwdfn1( state, next_func );
  }
}


#define init_history 0

#define max_fwd_children 4

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


static const int bw_max_children = 4;
#define max_bwd_children 4

/* initialise a backwards move iterator */
#define init_bwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = bwdfn0 ; \
  (*ruleid_iter).my_state = state; \
}

/* apply a rule to a state */
#define apply_bwd_rule( rule, state, result ) bwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define bwd_rule_valid_for_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_bwd_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 0 && state->vars[ 1 ] == 1 && state->vars[ 2 ] == 2 && state->vars[ 3 ] == 3 ) {
    return 1;
  }
  return 0;
}

static void init_goal_state( state_t *state, int goal_rule )
{
  switch( goal_rule ) {
  case 0:
    state->vars[ 0 ] = 0;
    state->vars[ 1 ] = 1;
    state->vars[ 2 ] = 2;
    state->vars[ 3 ] = 3;
    break;
  }
}

/* get the first goal state and initialise iterator */
#define first_goal_state( state_ptr, int_ptr_goal_iter ) init_goal_state(state_ptr,*(int_ptr_goal_iter)=0)

/* get the next goal state
   returns 1 if there is another goal state, 0 otherwise */
static int8_t next_goal_state( state_t *state, int *goal_iter )
{
  switch( *goal_iter ) {
  case 0:
    return 0;
  }
  return 0;
}

