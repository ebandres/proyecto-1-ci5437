#include "clases.h"

using namespace std;

int main() {

	char str[MAX_LINE_LENGTH + 1] = "1 b 2 3"; // Para la prueba se pone una representación del estado en string
	state_t state;
	list<pair<State,Action>> listaPar;
	ssize_t nchars = read_state(str, &state); // Esto convierte el str a un estado de psvn
	State initSt;
	initSt.state = state;
	cout << initSt.isGoalState() << endl;
	listaPar = initSt.succesors();
	Node start = make_root_node(initSt);
	Node* startPtr = &start;
	//print_state(stdout,&(start.state.state));

	for (auto const& i : listaPar) {
     	//print_state(stdout, &(i.first.state));
     	Node* newNode = start.make_node(i.first,startPtr,i.second);
     	print_state(stdout,&(newNode->state.state));
     	printf("\n");
     	cout << newNode->g << endl;
	}
}