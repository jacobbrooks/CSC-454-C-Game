#include <iostream>
#include "Room.h"
#include "PC.h"

using namespace std;

PC::PC(int the_ID, int t, Room* l): Creature(the_ID, t, l){
	Creature(the_ID, t, l);
	respect = 40;
}

int PC::get_respect(){
	return respect;
}

void PC::change_respect(int amount){
	respect += amount;
}

void PC::print_respect(){
	cout << "Respect is now " << respect << endl;
}