#ifndef _PC_H
#define _PC_H
#include <iostream>
#include "Creature.h"

class Room;

class PC: public Creature {
	int respect;
public:
	PC(int the_ID, int t, Room* l);
	int get_respect();
	void change_respect(int amount);
	void print_respect();
};

#endif