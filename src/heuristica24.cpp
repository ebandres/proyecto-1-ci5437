#include <iostream>
#include <algorithm>

using namespace std;

// Variables para guardar las pdb's
state_map_t *pdb1, *pdb2, *pdb3, *pdb4, *pdb5, *pdb6;

// Variables para guardar la especificación de la abstracción correspondiente
abstraction_t *abs1, *abs2, *abs3, *abs4, *abs5, *abs6;

/* Variables para almacenar estados, que son equivalentes al estado pasado
   como entrada, pero aplicando sus respectivas abstracciones */
state_t abst_state1;
state_t abst_state2;
state_t abst_state3;
state_t abst_state4;
state_t abst_state5;
state_t abst_state6;

// Variable para almacenar manhattan
unsigned mtable[16][16];

void set_pdb(){
	cout << "setting" << endl;
	FILE *f1 = fopen("24puzzle_1-5-6-7.pdb","r");
	FILE *f2 = fopen("24puzzle_2-3-4-9.pdb","r");
	FILE *f3 = fopen("24puzzle_8-13-14-18.pdb","r");
	FILE *f4 = fopen("24puzzle_10-11-12-17.pdb","r");
	FILE *f5 = fopen("24puzzle_15-16-20-21.pdb","r");
	FILE *f6 = fopen("24puzzle_19-22-23-24.pdb","r");

	pdb1 = read_state_map(f1);
	cout << "read1" << endl;
	pdb2 = read_state_map(f2);
	cout << "read2" << endl;
	pdb3 = read_state_map(f3);
	cout << "read3" << endl;
	pdb4 = read_state_map(f4);
	cout << "read4" << endl;
	pdb5 = read_state_map(f5);
	cout << "read5" << endl;
	pdb6 = read_state_map(f6);
	cout << "read6" << endl;


	abs1 = read_abstraction_from_file("24puzzle_1-5-6-7.abst");
	abs2 = read_abstraction_from_file("24puzzle_2-3-4-9.abst");
	abs3 = read_abstraction_from_file("24puzzle_8-13-14-18.abst");
	abs4 = read_abstraction_from_file("24puzzle_10-11-12-17.abst");
	abs5 = read_abstraction_from_file("24puzzle_15-16-20-21.abst");
	abs6 = read_abstraction_from_file("24puzzle_19-22-23-24.abst");

	fclose(f1);
	fclose(f2);
	fclose(f3);	
	fclose(f4);
	fclose(f5);
	fclose(f6);
	cout << "set" << endl;
}

unsigned pdb_add(state_t s){
	abstract_state(abs1, &s, &abst_state1);
	abstract_state(abs2, &s, &abst_state2);
	abstract_state(abs3, &s, &abst_state3);
	abstract_state(abs4, &s, &abst_state4);
	abstract_state(abs5, &s, &abst_state5);
	abstract_state(abs6, &s, &abst_state6);

	unsigned sum = *state_map_get(pdb1, &abst_state1) + *state_map_get(pdb2, &abst_state2) + *state_map_get(pdb3, &abst_state3)
						+ *state_map_get(pdb4, &abst_state4) + *state_map_get(pdb5, &abst_state5) + *state_map_get(pdb6, &abst_state6);
	//unsigned sum = max({*state_map_get(pdb1, &abst_state1), *state_map_get(pdb2, &abst_state2), *state_map_get(pdb3, &abst_state3)});

	return sum;
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