#include <iostream>
#include "Room.h"
#include "PC.h"
#include "Animal.h"

using namespace std;

Animal::Animal(int the_ID, int t, Room* l): Creature(the_ID, t, l){
	Creature(the_ID, t, l);
	anti_preference = 2;
}

void Animal::react(int action, int type){
	string reaction[2] = {"licks your face", "growels"};
	int respect_change[2] = {1, -1};
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

bool Animal::should_change_rooms(){
	if(location -> get_state() == anti_preference){
		return true;
	}
	return false;
}
