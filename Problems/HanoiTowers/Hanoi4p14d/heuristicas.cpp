#include <iostream>
#include <algorithm>

using namespace std;

// Variables para guardar las pdb's
state_map_t *pdb1, *pdb2;

// Variables para guardar la especificación de la abstracción correspondiente
abstraction_t *abs1, *abs2;

/* Variables para almacenar estados, que son equivalentes al estado pasado
   como entrada, pero aplicando sus respectivas abstracciones */
state_t abst_state1;
state_t abst_state2;

// Variable para almacenar manhattan
unsigned mtable[16][16];

void set_pdb(){
	FILE *f1 = fopen("absHanoi14_1.pdb","r");
	FILE *f2 = fopen("absHanoi14_2.pdb","r");

	pdb1 = read_state_map(f1);
	pdb2 = read_state_map(f2);

	abs1 = read_abstraction_from_file("absHanoi14_1.abst");
   abs2 = read_abstraction_from_file("absHanoi14_2.abst");

	fclose(f1);
	fclose(f2);
}

unsigned pdb_add(state_t s){
	abstract_state(abs1, &s, &abst_state1);
	abstract_state(abs2, &s, &abst_state2);
	unsigned max;

	//unsigned max = *state_map_get(pdb1, &abst_state1) + *state_map_get(pdb2, &abst_state2) + *state_map_get(pdb3, &abst_state3);
	//unsigned max = max({*state_map_get(pdb1, &abst_state1), *state_map_get(pdb2, &abst_state2)});

	if ((*state_map_get(pdb1, &abst_state1)) > (*state_map_get(pdb2, &abst_state2))) {
		max = *state_map_get(pdb1, &abst_state1);
	} else {
		max = *state_map_get(pdb2, &abst_state2);
	}

	return max;
}

void set_manhattan(){
	unsigned prov[16][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						   {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
						   {2,1,0,1,3,2,1,2,4,3,2,3,5,4,3,4},
						   {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
						   {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
						   {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
						   {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
						   {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
						   {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
						   {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
						   {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
						   {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
						   {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
						   {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
						   {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
						   {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}};

	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			mtable[i][j] = prov[i][j];
		}
	}
}

unsigned manhattan(state_t state){
   unsigned h=0;
   for (int i=0; i<=15; i++){
      h += mtable[state.vars[i]][i];
   }
   return h;
}