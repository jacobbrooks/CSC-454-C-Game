#include <iostream>
#include "Room.h"
#include "Creature.h"
#include "Game.h"
#include "Human.h"
#include "Animal.h"

using namespace std;

Room::Room(int the_ID){
	id = the_ID;
	for(int i = 0; i < 4; i++){
		neighbors[i] = NULL;
	}
	creature_count = 0;
	string the_directions[4] = {"north", "south", "east", "west"};
	for(int i = 0; i < 4; i++){
		directions[i] = the_directions[i];
	}
}

void Room::set_state(int st){
	state = st;
}

void Room::set_neighbors(Room* n[4]){
	for(int i = 0; i < 4; i++){
		neighbors[i] = n[i];
	}	
}

int Room::get_ID(){
	return id;
}

int Room::get_state(){
	return state;
}

void Room::change_state(int amount){
	state += amount;
}

Room* Room::neighbor_at(int i){
	return neighbors[i];
}

Creature* Room::creature_at(int i){
	return occupants[i];
}

int Room::get_creature_count(){
	return creature_count;
}

void Room::add_creature(Creature* c){
	occupants.push_back(c);
	creature_count++;
}

void Room::remove_creature(Creature* c){
	for(int i = 0; i < creature_count; i++){
		if(occupants[i] -> get_ID() == c -> get_ID()){
			occupants.erase(occupants.begin() + i);
		}
	}
	creature_count--;
}

string Room::state_string(){
	if(state == 0){
		return "clean";
	}else if(state == 1){
		return "half-dirty";
	}
	return "dirty";
}

string Room::direction_at(int i){
	return directions[i];
}

int Room::direction_index(string direction){
	int index;
	for(int i = 0; i < 4; i++){
		if(direction.compare(directions[i]) == 0){
			index = i;
		}
	}
	return index;
}

int Room::rand_room(){
	srand(time(NULL));
	int random_number = rand() % 4;
	while(neighbors[random_number] == NULL || neighbors[random_number] -> is_full()){
		random_number = rand() % 4;
	}
	return random_number;
}

bool Room::is_full(){
	if(creature_count == 10){
		return true;
	}
	return false;
}

bool Room::all_neighbors_full(){
	for(int i = 0; i < 4; i++){
		if(neighbors[i] != NULL){
			if(!neighbors[i] -> is_full()){
				return false;
			}
		}
	}
	return true;
}

void Room::incite_room_state_reactions(Game* g, int action, Creature* c){
	int frozen_creature_count = creature_count;
	Creature* creatures[frozen_creature_count];
	for(int i = 0; i < frozen_creature_count; i++){ //Have to make a static array of creatures to loop through because the indexes of the creatures in the 'occupants[]'
		creatures[i] = occupants[i];		//vector change dynamically throughout execution this function
	}
	for(int i = 0; i < frozen_creature_count; i++){
		if(creatures[i] -> get_type() == 1){
			Animal* a = static_cast<Animal*>(creatures[i]);
			if(a -> get_ID() == c -> get_ID()){
				a -> react(action, 1);
			}else{
				a -> react(action, 0);
			}if(a -> should_change_rooms()){
				if(!all_neighbors_full()){
					a -> change_rooms(directions[rand_room()]);
				}else{
					send_through_roof(g, creatures[i]);
					incite_negative_reactions();
				}
			}
		}else if(creatures[i] -> get_type() == 2){
			Human* h = static_cast<Human*>(creatures[i]);
			if(h -> get_ID() == c -> get_ID()){
				h -> react(action, 1);
			}else{
				h -> react(action, 0);
			}if(h -> should_change_rooms()){
				if(!all_neighbors_full()){
					h -> change_rooms(directions[rand_room()]);
				}else{
					send_through_roof(g, creatures[i]);
					incite_negative_reactions();
				}
			}
		}
	}
}

void Room::incite_negative_reactions(){
	for(int i = 0; i < creature_count; i++){
		if(occupants[i] -> get_type() == 1){
			Animal* a = static_cast<Animal*>(occupants[i]);
			a -> react(1, 0);
		}else if(occupants[i] -> get_type() == 2){
			Human* h = static_cast<Human*>(occupants[i]);
			h -> react(0, 0);
		}
	}
}

void Room::send_through_roof(Game* g, Creature* c){
	int index_in_occupants;
	for(int i = 0; i < creature_count; i++){
		if(c -> get_ID() == occupants[i] -> get_ID()){
			index_in_occupants = i;
		}
	}
	Creature* creature_to_delete = c;
	int creature_ID = creature_to_delete -> get_ID();
	string type = creature_to_delete -> type_string();
	for(int j = 0; j < g -> creatures.size(); j++){
		if(g -> creatures[j] -> get_ID() == creature_ID){
			g -> creatures.erase(g -> creatures.begin() + j);
		}
	}
	cout << type << " " << creature_ID << " drills a hole through the ceiling, and leaves." << endl;
	remove_creature(creature_to_delete);
	delete creature_to_delete;
}	




