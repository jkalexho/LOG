//Tile class
#include <string>
#include "Globals.h"
#include "Tileset.h"

using namespace std;



#ifndef Tile_H
#define Tile_H
class Object;
class Tile
{
public:
	//Default Constructor
	Tile();
	//Overload Constructor
	Tile(int, int, Tileset*, Object*);

	Tile(Tileset*);

	~Tile();

	void setX(int);

	void setY(int);

	void setTileset(Tileset*);

	void addOccupant(Object*);

	void removeOccupant(Object*);

	void setNeighbor(int, Tile*);

	Tile** getNeighbors();

	int getPassability();

	int getWidth();

	int getHeight();

	int getX();
	
	int getY();

	void render(int, int);

	Tileset* getTileset();

	Object** getOccupants();

private:
	int x;
	int y;
	int pass;
	Tileset* t;
	Tile* neighbors[8];
	Object* occupants[OCCUPANTS];
	int offsetX;
	SDL_Rect clip;
};

#endif

