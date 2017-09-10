#ifndef _Human_H
#define _Human_H
#include <iostream>
#include "Creature.h"

class Room;
class PC;

class Human: public Creature {
	int anti_preference;
public:
	Human(int the_ID, int t, Room* l);
	void react(int action, int type);
	bool should_change_rooms();
};

#endif