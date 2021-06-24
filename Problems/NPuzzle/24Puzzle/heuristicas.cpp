#include <iostream>
#include <algorithm>

using namespace std;

// Variables para guardar las pdb's
state_map_t *pdb1, *pdb2, *pdb3, *pdb4, *pdb5, *pdb6, *pdb7, *pdb8;

// Variables para guardar la especificación de la abstracción correspondiente
abstraction_t *abs1, *abs2, *abs3, *abs4, *abs5, *abs6, *abs7, *abs8;

/* Variables para almacenar estados, que son equivalentes al estado pasado
   como entrada, pero aplicando sus respectivas abstracciones */
state_t abst_state1;
state_t abst_state2;
state_t abst_state3;
state_t abst_state4;
state_t abst_state5;
state_t abst_state6;
//state_t abst_state7;
//state_t abst_state8;

void set_pdb(void){
	FILE *f1 = fopen("24puzzle1.pdb","r");
	FILE *f2 = fopen("24puzzle2.pdb","r");
	FILE *f3 = fopen("24puzzle3.pdb","r");
	FILE *f4 = fopen("24puzzle4.pdb","r");
	FILE *f5 = fopen("24puzzle5.pdb","r");
	FILE *f6 = fopen("24puzzle6.pdb","r");
	//FILE *f7 = fopen("24puzzle7.pdb","r");
	//FILE *f8 = fopen("24puzzle8.pdb","r");

	cout << 1 << endl;
	pdb1 = read_state_map(f1);
	cout << 2 << endl;
	pdb2 = read_state_map(f2);
	cout << 3 << endl;
	pdb3 = read_state_map(f3);
	cout << 4 << endl;
	pdb4 = read_state_map(f4);
	cout << 5 << endl;
	pdb5 = read_state_map(f5);
	cout << 6 << endl;
	pdb6 = read_state_map(f6);
	//pdb7 = read_state_map(f7);
	//pdb8 = read_state_map(f8);

	abs1 = read_abstraction_from_file("24puzzle1.abst");
    abs2 = read_abstraction_from_file("24puzzle2.abst");
    abs3 = read_abstraction_from_file("24puzzle3.abst");
    abs4 = read_abstraction_from_file("24puzzle4.abst");
    abs5 = read_abstraction_from_file("24puzzle5.abst");
    abs6 = read_abstraction_from_file("24puzzle6.abst");
    //abs7 = read_abstraction_from_file("24puzzle7.abst");
    //abs8 = read_abstraction_from_file("24puzzle8.abst");

	fclose(f1);
	fclose(f2);
	fclose(f3);	
	fclose(f4);	
	fclose(f5);	
	fclose(f6);	
	//fclose(f7);	
	//fclose(f8);	
}

unsigned pdb_add(state_t s){
	abstract_state(abs1, &s, &abst_state1);
	abstract_state(abs2, &s, &abst_state2);
	abstract_state(abs3, &s, &abst_state3);
	abstract_state(abs4, &s, &abst_state4);
	abstract_state(abs5, &s, &abst_state5);
	abstract_state(abs6, &s, &abst_state6);
	//abstract_state(abs7, &s, &abst_state7);
	//abstract_state(abs8, &s, &abst_state8);

	unsigned sum = *state_map_get(pdb1, &abst_state1) + *state_map_get(pdb2, &abst_state2) + *state_map_get(pdb3, &abst_state3) + *state_map_get(pdb4, &abst_state4)
		+ *state_map_get(pdb5, &abst_state5) + *state_map_get(pdb6, &abst_state6);
	//unsigned sum = max({*state_map_get(pdb1, &abst_state1), *state_map_get(pdb2, &abst_state2), *state_map_get(pdb3, &abst_state3)});

	return sum;
}
