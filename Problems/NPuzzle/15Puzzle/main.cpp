#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <cstring>
#include <fstream>
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

	cout << "Input option:\n\t1 Manhattan\n\t2 PDB" << endl;
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1; 
	}
	cout << endl;

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

	string line;
	ifstream myFile ("input.txt");

	if (myFile.is_open()) 
	{
		ofstream resultFile ("results.txt", ios::out | ios::trunc);

		while ( getline(myFile, line) )
    	{
			strcpy(str, line.c_str());
			nchars = read_state(str, init);
			if (nchars <= 0) {
				cout << "Invalid state" << endl;
				return 2; 
			}
			cout << "\nstate:" << endl;
			print_state(stdout, init);
			cout << endl;

			resultFile << "\nstate:\n" << str << endl;

			int64_t generatedNodes = 1;

			auto start = high_resolution_clock::now();

			try
			{
				result = ida_search(init, heuristic, true, generatedNodes, start);
			}
			catch(int e)
			{
				if (e == 3)
				{
					cout << "Time limit reached" << endl;
					resultFile << "Time limit reached" << endl;
				}
				else
				{
					cout << "Error code " << e << endl;
					resultFile << "Error code " << e << endl;
				}
				result.clear();
				
			}
			

			auto stop = high_resolution_clock::now();

			duration<double> total = stop - start;
			cout << "time: " << total.count() << " s\t" << "solution length: " << result.size() << endl;
			resultFile << "time: " << total.count() << " s\t" << "solution length: " << result.size() << endl;
			cout << "generated nodes: " << generatedNodes << endl;
			resultFile << "generated nodes: " << generatedNodes << endl;
    	}
    	resultFile.close();
		myFile.close();
	}


	/*
	cout << "Input initial state:\n";
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1; 
	}
	// Convert the string to a state
	nchars = read_state(str, init);
	
	print_state(stdout, init);
	if (nchars <= 0) {
		cout << "Invalid state" << endl;
		return 2; 
	}



	int64_t generatedNodes = 1;
	auto start = high_resolution_clock::now();

	result = ida_search(init,heuristic,true, generatedNodes);

	auto stop = high_resolution_clock::now();
	duration<double> total = stop - start;
	cout << "time: " << total.count() << " s\t" << "solution length: " << result.size() << endl;
	cout << generatedNodes << endl;
	*/
}