#ifndef _PC_H
#define _PC_H
#include <iostream>
#include "Creature.h"

class Room;

class PC: public Creature {
	int respect;
public:
	PC(int the_ID, int t, Room* l): Creature(the_ID, t, l){
		respect = 40;
	}
	~PC();
	int get_respect();
	void change_respect(int amount);
	void print_respect();
	void react(int action, int type);
	bool should_change_rooms();
	void react_negative();
};

#endif
