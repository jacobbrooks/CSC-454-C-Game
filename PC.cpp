#include <iostream>
#include "Room.h"
#include "PC.h"

using namespace std;

int PC::get_respect(){
	return respect;
}

void PC::change_respect(int amount){
	respect += amount;
}

void PC::print_respect(){
	cout << "Respect is now " << respect << endl;
}

void PC::react(int action, int type){
}

bool PC::should_change_rooms(){
}

void PC::react_negative(){
}
