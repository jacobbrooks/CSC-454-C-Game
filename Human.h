#ifndef _Human_H
#define _Human_H
#include <iostream>
#include "Creature.h"

class Room;
class PC;

class Human: public Creature {
	int anti_preference;
public:
	Human(int the_ID, int t, Room* l):Creature(the_ID, t, l){
		anti_preference = 0;
	}
	~Human();
	void react(int action, int type);
	bool should_change_rooms();
	void react_negative();
};

#endif
