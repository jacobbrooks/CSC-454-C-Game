#ifndef _Game_H
#define _Game_H
#include <iostream>
#include <vector>
#include <string>
#include "PC.h"

class Room;
class Creature;

class Game{
	bool game_over();
	void free_all_memory();
	void init_rooms();
	void init_creatures();
public: 
	std::vector<Room*> rooms;
	std::vector<Creature*> creatures;
	PC* the_PC;
	Creature* get_creature(int id);
	bool creature_exists(int id);
	void main();
};

#endif
