#include <iostream>
#include <cstdlib>
#include <vector>
#include "Game.h"
#include "Room.h"
#include "Creature.h"
#include "Animal.h"
#include "Human.h"
#include <ctype.h>

using namespace std;

void Game::init_rooms(){
	int num_rooms;
	cin >> num_rooms;
	for(int i = 0; i < num_rooms; i++){
		Room* r = new Room(i);
		rooms.push_back(r);
	}
	for(int i = 0; i < num_rooms; i++){
		int inputs[5]; //cin reads into this: [0] = state, [1] = north, [2] = south, etc.
		Room* neighbors[4];
		cin >> inputs[0] >> inputs[1] >> inputs[2] >> inputs[3] >> inputs[4];
		rooms[i] -> set_state(inputs[0]);
		for(int j = 1; j < 5; j++){
			if(inputs[j] != -1){
				neighbors[j - 1] = rooms[inputs[j]]; 
			}else{
				neighbors[j - 1] = NULL;
			}
		}
		rooms[i] -> set_neighbors(neighbors);
	}
}

void Game::init_creatures(){
	int num_creatures;
	cin >> num_creatures;
	for(int i = 0; i < num_creatures; i++){
		int type, location;
		cin >> type >> location;
		Room* creature_location = rooms[location];
		if(type == 0){
			PC* p = new PC(i, type, creature_location);
			creatures.push_back(p);
			the_PC = p; 
			creature_location -> add_creature(p);
		}else if(type == 1){
			Animal* a = new Animal(i, type, creature_location);
			creatures.push_back(a);
			creature_location -> add_creature(a);
		}else{
			Human* h = new Human(i, type, creature_location);
			creatures.push_back(h);
			creature_location -> add_creature(h);
		}
	}
}

void Game::free_all_memory(){
	for(int i = 0; i < creatures.size(); i++){
		delete creatures[i];
	}
	for(int i = 0; i < rooms.size(); i++){
		delete rooms[i];
	}
}

Creature* Game::get_creature(int id){
	Creature* c = NULL;
	for(int i = 0; i < creatures.size(); i++){
		if(creatures[i] -> get_ID() == id){
			c = creatures[i];
		}
	}
	return c;
}

bool Game::creature_exists(int id){
	for(int i = 0; i < creatures.size(); i++){
		if(creatures[i] -> get_ID() == id){
			return true;
		}
	}
	return false;
}

bool Game::game_over(){
	if(the_PC -> get_respect() >= 80){
		cout << "\nYou win!" << endl;
		return true;
	}else if(the_PC -> get_respect() <= 0){
		cout << "\nYou Lose!" << endl;
		return true;
	}
	return false;
}

int colon_index(std::string command){
	int index = -1;
	for(int i = 0; i < command.length(); i++){
		if(command.at(i) == ':'){
			index = i;
		}
	}
	return index;
}

int creature_ID(std::string command){
	char digits[command.length()];
	for(int i = 0; i < command.length(); i++){
		digits[i] = command.at(i);
	}
	int creature = std::atoi(digits);
	return creature;
}

void Game::main(){
	init_rooms();
	init_creatures();
	string command; 
	cin >> command;
	Creature* actor;
	int actor_ID;

	while(command.compare("exit")){
		actor = the_PC;
		actor_ID = the_PC -> get_ID();
		if(isdigit(command.at(0))){
			actor_ID = creature_ID(command);
		}
		if(creature_exists(actor_ID) && the_PC -> get_location() == get_creature(actor_ID) -> get_location()){
			actor = get_creature(actor_ID);
			int colon = colon_index(command);
			std::string order;
			if(colon != -1){
				order = command.substr(colon + 1, (command.length() - (unsigned long) (colon + 1)));
			}else{
				order = command;
			}
			if(!order.compare("look")){
				actor -> look();
			}else if(!order.compare("clean")){
				if(actor -> clean()){
					actor -> get_location() -> incite_room_state_reactions(this, 0, actor);
				}else{
					cout << "The room is already clean." << endl;
				}
			}else if(!order.compare("dirty")){
				if(actor -> dirty()){
					actor -> get_location() -> incite_room_state_reactions(this, 1, actor);
				}else{
					cout << "The room is already dirty." << endl;
				}
			}else if(order.compare("north") && order.compare("south") 
				&& order.compare("east") && order.compare("west")){
				cout << "'" << order << "' is not a valid command." << endl;
			}else if(actor -> get_location() -> neighbor_at(actor -> get_location() -> direction_index(order)) != NULL){
				if(!actor -> change_rooms(order)){
					cout << "Room to the " << order << " is full." << endl;
					actor -> react_negative();
				}		    
			}else{
				cout << "There is no room to the " << order << "." << endl;
			}
		}else{
			cout << actor_ID << " is not in the room or does not exist." << endl;
		}
		if(game_over()){
			break;
		}
		cout << endl;
		cin >> command;
	}

	cout << endl;
	cout << "Goodbye!" << endl;
	free_all_memory();
}

int main(){
	Game* g = new Game();
	g -> main();
	return 0;
}
