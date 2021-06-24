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
#include "ida.h"

using namespace std;
using namespace std::chrono;


unsigned (*heuristic) (state_t);

ifstream myFile;
ofstream resultFile;

void signal_callback_handler(int signum) {
	if (myFile.is_open())
	{
		myFile.close();
	}

	if (resultFile.is_open())
	{
		resultFile << "\nProgram terminated by user" << endl;
		resultFile.close();
	}
	
	exit(signum);
}

int main(void) {
	signal(SIGINT, signal_callback_handler);

	vector<int> result;
	int result_a;
	state_t *init = new state_t;
	char str[300 + 1]; // Para la prueba se pone una representación del estado en string
	ssize_t nchars;

	cout << "Select algorithm:\n\t1 - A*\n\t2 - IDA*" << endl;
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1;
	}

	int alg = atoi(str); // For later

	cout << "Input option:\n\t1 - Additive PDB" << endl;
	if (fgets(str, sizeof(str), stdin) == NULL) {
		cout << "No input" << endl;
		return 1; 
	}
	cout << endl;

	int selection = atoi(str); // Leftover from multiple option selection


	set_pdb();
	heuristic = pdb_add;
	

	string line;
	myFile.open("input.txt");

	if (myFile.is_open()) 
	{
		string filename = "results_" + to_string(alg) + "_" + to_string(selection) + ".txt";
		resultFile.open(filename, ios::out | ios::trunc);

		resultFile << "These results were obtained using ";

		switch (alg)
		{
		case 1:
			resultFile << "A* with ";
			break;
		
		case 2:
			resultFile << "IDA* with ";
			break;
		}


		resultFile << "Additive PDB Heuristic" << endl;


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

			time_point<high_resolution_clock> start;

			try
			{
				switch (alg)
				{
				case 1:
					start = high_resolution_clock::now();
					result_a = a_search(init, heuristic, true, generatedNodes, start);
					break;
				
				case 2:
					start = high_resolution_clock::now();
					result = ida_search(init, heuristic, true, generatedNodes, start);
					break;
				}
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
				result_a = 0;
			}
			

			auto stop = high_resolution_clock::now();

			duration<double> total = stop - start;
			cout << "time: " << total.count() << " s\t";
			resultFile << "time: " << total.count() << " s\t";
			switch (alg)
			{
			case 1:
				cout << "solution cost: " << result_a << endl;
				resultFile << "solution cost: " << result_a << endl;
				break;
			
			case 2:
				cout << "solution length: " << result.size() << endl;
				resultFile << "solution length: " << result.size() << endl;
				break;
			}
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