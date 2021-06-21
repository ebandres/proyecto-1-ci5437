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

int main(void) {

	vector<int> result;
	state_t *init = new state_t;
	char str[300 + 1]; // Para la prueba se pone una representación del estado en string
	ssize_t nchars;

	cout << "Input initial state:\n";
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1; 
	}
	cout << "Helpe" << endl;
	// Convert the string to a state
	nchars = read_state(str, init);
	print_state(stdout, init);
	if (nchars <= 0) {
		cout << "Invalid state" << endl;
		return 2; 
	}

	cout << "Input option:\n\t1 Manhattan\n\t2 PDB" << endl;
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1; 
	}

	int selection = atoi(str);

	switch (selection)
	{
	case 1:
		set_manhattan();
		heuristic = manhattan;
		break;
	case 2:
		set_pdb();
		heuristic = pdb_add;
		break;
	}

	int64_t nums = 1;
	int64_t generatedNodes = 1;
	auto start = high_resolution_clock::now();

	result = ida_search(init,heuristic,true, generatedNodes);

	auto stop = high_resolution_clock::now();
	duration<double> total = stop - start;
	cout << "time: " << total.count() << " s\t" << "solution length: " << result.size() << endl;
	cout << generatedNodes << endl;
}