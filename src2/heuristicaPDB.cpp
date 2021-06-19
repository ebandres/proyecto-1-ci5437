#include <iostream>

// Variables para guardar las pdb's
state_map_t *pdb1, *pdb2, *pdb3;

// Variables para guardar la especificación de la abstracción correspondiente
abstraction_t *abs1, *abs2, *abs3;

/* Variables para almacenar estados, que son equivalentes al estado pasado
   como entrada, pero aplicando sus respectivas abstracciones */
state_t abst_state1;
state_t abst_state2;
state_t abst_state3;

void establishHeuristic(){
	FILE *f1 = fopen("15-puzzle_1-2-3-6-7.pdb","r");
	FILE *f2 = fopen("15-puzzle_4-5-8-9-12.pdb","r");
	FILE *f3 = fopen("15-puzzle_10-11-13-14-15.pdb","r");

	pdb1 = read_state_map(f1);
	pdb2 = read_state_map(f2);
	pdb3 = read_state_map(f3);

	abs1 = read_abstraction_from_file("15-puzzle_1-2-3-6-7.abst");
    abs2 = read_abstraction_from_file("15-puzzle_4-5-8-9-12.abst");
    abs3 = read_abstraction_from_file("15-puzzle_10-11-13-14-15.abst");

	fclose(f1);
	fclose(f2);
	fclose(f3);	
}

unsigned heuristic(state_t s){
	abstract_state(abs1, &s, &abst_state1);
	abstract_state(abs2, &s, &abst_state2);
	abstract_state(abs3, &s, &abst_state3);

	unsigned sum = *state_map_get(pdb1, &abst_state1) + *state_map_get(pdb2, &abst_state2) + *state_map_get(pdb3, &abst_state3);

	return sum;
}
