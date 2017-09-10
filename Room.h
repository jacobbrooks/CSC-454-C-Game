#ifndef _Room_H
#define _Room_H
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

class Creature;
class Game;

class Room{
	int id;
	int state;
	int creature_count;
	Room* neighbors[4];
	std::vector<Creature*> occupants;
	std::string directions[4];
public:
	Room(int the_ID);
	void set_state(int st);
	void change_state(int amount);
	void set_neighbors(Room* n[4]);
	int get_ID();
	int get_state();
	Room* neighbor_at(int i);
	Creature* creature_at(int i);
	int get_creature_count();
	void add_creature(Creature* c);
	void remove_creature(Creature* c);
	std::string state_string();
	std::string direction_at(int i);
	int direction_index(std::string direction);
	int rand_room();
	bool is_full();
	bool all_neighbors_full();
	void incite_room_state_reactions(Game* g, int action, Creature* c);
	void incite_negative_reactions();
	void send_through_roof(Game* g, Creature* c);
};

#endif
