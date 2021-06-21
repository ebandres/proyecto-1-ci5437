#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "ida.h"

using namespace std;
using namespace std::chrono;


unsigned (*heuristic) (state_t);

int main() {

	vector<int> result;
	state_t *init;
	//char str[100 + 1] = "14 1 9 6 4 8 12 5 7 2 3 B 10 11 13 15"; // Para la prueba se pone una representación del estado en string
	char str[100 + 1] = "0 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0"; 
	ssize_t nchars = read_state(str, init); // Esto convierte el str a un estado de psvn

	cout << "Input option:\n\t1 Manhattan\n\t2 PDB" << endl;
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input.\n";
		return 1; 
	}

	int selection = atoi(str);

	switch (selection)
	{
	case 1:
		cout << "man" << endl;
		set_manhattan();
		heuristic = manhattan;
		break;
	case 2:
		cout << "pdb" << endl;
		set_pdb();
		heuristic = pdb_add;
		break;
	}

	auto start = high_resolution_clock::now();

	result = ida_search(init,heuristic,true);
	//unsigned test = heuristic(*init);
	//cout << "HEURISTIC VALUE: " << test << endl;
	auto stop = high_resolution_clock::now();
	duration<double> total = stop - start;
	cout << "time: " << total.count() << " segundos" << endl;
}