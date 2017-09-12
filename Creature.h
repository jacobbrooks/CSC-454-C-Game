#ifndef _Creature_H
#define _Creature_H
#include <iostream>
#include <string>

class Room;
class PC;

class Creature{
public:
	Creature(int the_ID, int t, Room* l);
	void set_location(Room* l);
	int get_ID();
	int get_type();
	Room* get_location();
	std::string type_string();
	void look();
	bool change_rooms(std::string direction);
	PC* get_PC();
	bool clean();
	bool dirty();
	virtual void react(int action, int type) = 0;
	virtual bool should_change_rooms() = 0;
	virtual void react_negative() = 0;
	
protected:
	int id;
	int type;
	Room* location;
};

#endif
