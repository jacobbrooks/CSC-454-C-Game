#include <iostream>
#include "Creature.h"
#include "Room.h"
#include "PC.h"

using namespace std;

Creature::Creature(int the_ID, int t, Room* l){
	id = the_ID;
	type = t;
	location = l;
}

Creature::~Creature(){}; //Doesn't need to do anything except exist

int Creature::get_ID(){
	return id;
}

int Creature::get_type(){
	return type;
}

Room* Creature::get_location(){
	return location;
}

PC* Creature::get_PC(){
	PC* the_PC = NULL;
	for(int i = 0; i < location -> get_creature_count(); i++){
		if(location -> creature_at(i) -> get_type() == 0){
			the_PC = static_cast<PC*>(location -> creature_at(i));
		}
	}
	return the_PC;
}

string Creature::type_string(){
	if(type == 0){
		return "PC";
	}else if(type == 1){
		return "Animal";
	}
	return "Human";
}

void Creature::look(){
	string state = location -> state_string();
	int room_ID = location -> get_ID();
	cout << "Room " << room_ID << ", " << state << ", neighbors ";
	for(int i = 0; i < 4; i++){
		if(location -> neighbor_at(i) != NULL){
			int neighbor_ID = location -> neighbor_at(i) -> get_ID();
			string direction = location -> direction_at(i);
			cout << neighbor_ID << " to the " << direction << ", ";
		}
	}
	cout << "contains: " << endl;
	for(int i = 0; i < location -> get_creature_count(); i++){
		string creature_type = location -> creature_at(i) -> type_string();
		int creature_ID = location -> creature_at(i) -> get_ID();
		if(creature_type.compare("PC")){
			cout << creature_type << " " << creature_ID << endl;
		}else{
			cout << creature_type << endl;
		}
	}
}

bool Creature::change_rooms(string direction){
	int neighbor_index = location -> direction_index(direction);
	if(location -> neighbor_at(neighbor_index) -> is_full()){
		return false;
	}
	Creature* c = NULL;
	for(int i = 0; i < location -> get_creature_count(); i++){
		if(location -> creature_at(i) -> get_ID() == id){
			c = location -> creature_at(i);
		}
	}
	Room* r = location -> neighbor_at(neighbor_index);
	r -> add_creature(c);
	location -> remove_creature(c);
	location = r;
	if(type == 0){
		cout << "You leave towards the " << direction << "." << endl;
	}else{
		cout << id << " leaves towards the " << direction << "." << endl;
		if(type == 1){
			if(location -> get_state() == 2){
				clean();
			}
		}else{
			if(location -> get_state() == 0){
				dirty();
			}
		}
	}
	return true;
}

bool Creature::clean(){
	if(location -> get_state() != 0){
		location -> change_state(-1);
		return true;
	}
	return false;
}

bool Creature::dirty(){
	if(location -> get_state() != 2){
		location -> change_state(1);
		return true;
	}
	return false;
}




