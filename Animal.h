#ifndef _Animal_H
#define _Animal_H
#include <iostream>
#include "Creature.h"

class Room;
class PC;

class Animal: public Creature{
	int anti_preference;
public:
	Animal(int the_ID, int t, Room* l) : Creature(the_ID, t, l){
		anti_preference = 2;
	}
	void react(int action, int type);
	bool should_change_rooms();
	void react_negative();
};

#endif
