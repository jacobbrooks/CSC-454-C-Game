output: Room.o Game.o Creature.o PC.o Animal.o Human.o 
	g++ Room.o Game.o Creature.o PC.o Animal.o Human.o  -o game

Room.o: Room.cpp Room.h
	g++ -c Room.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

Creature.o: Creature.cpp Creature.h
	g++ -c Creature.cpp;

PC.o: PC.cpp PC.h
	g++ -c PC.cpp;

Animal.o: Animal.cpp Animal.h
	g++ -c Animal.cpp;

Human.o: Human.cpp Human.h
	g++ -c Human.cpp;

clean:
	rm *.o game
