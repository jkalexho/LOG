#include "Tile.h"
#include "Object.h"
#include "Globals.h"
#include <string>

#ifndef BOARD_H
#define BOARD_H
class Board
{
public:
	Board();

	Board(Tileset*, int, int);

	~Board();

	Tile* getTile(int, int);

	bool exists(int, int);

	void render(SDL_Renderer*, int, int, int, int, float, float, float);

private:
	Tile** board;
	int width;
	int height;
};
#endif
