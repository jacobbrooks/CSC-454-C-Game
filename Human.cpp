#include <iostream>
#include "Room.h"
#include "PC.h"
#include "Human.h"

using namespace std;

Human::~Human(){} //Doesn't need to do anything but exist

void Human::react(int action, int type){
	string reaction[2] = {"grumbles", "smiles"};
	int respect_change[2] = {-1, 1};
	PC* the_PC = get_PC();
	cout << id << " " << reaction[action];
	the_PC -> change_respect(respect_change[action]);
	if(type == 1){
		cout << " a lot"; 
		the_PC -> change_respect(2 * respect_change[action]);
	}
	cout << ". ";
	the_PC -> print_respect();
}

bool Human::should_change_rooms(){
	if(location -> get_state() == anti_preference){
		return true;
	}
	return false;
}

void Human::react_negative(){
 	 react(0,0);
}

