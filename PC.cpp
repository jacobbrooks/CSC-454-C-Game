#include <iostream>
#include "Room.h"
#include "PC.h"

using namespace std;

PC::~PC(){} //Doesn't need to do anything but exist

int PC::get_respect(){
	return respect;
}

void PC::change_respect(int amount){
	respect += amount;
}

void PC::print_respect(){
	cout << "Respect is now " << respect << endl;
}

void PC::react(int action, int type){ //No need for implementation
}

bool PC::should_change_rooms(){ //No need for implementation but still has to return something
	return false;
}

void PC::react_negative(){ //No need for implementation
}
