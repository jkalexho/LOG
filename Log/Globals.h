#include <string>

using namespace std;

#ifndef GLOBALS_H
#define GLOBALS_H

enum Tilesets {
	ZERO_TILE,
	BASIC_TILE,
	TOTAL_TILE,
};


enum Passability {
	IMPASSABLE,
	WALL,
	FORCEFIELD,
	OCCUPIED,
	PASSABLE,
	PASS_TOTAL
};

enum Direction {
	NORTHWEST,
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
};

enum Action {
	IDLE,
	MOVE,
	ATTACK,
	ACTION
};

enum Occupant {
	MOVETO,
	PHYSICAL,
	GHOST,
	PLAYER,
	SFX,
	OCCUPANTS
};

extern const int TILESET_SIZE;


#endif
