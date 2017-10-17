#include <string>
#include "Tile.h"

using namespace std;

#ifndef OBJECTS_H
#define OBJECTS_H

class Object
{
public:
	Object();

	~Object();

	Tile* getTile();

	int getPassability();

	int getGhost();

	void setTile(Tile*);

	void changeTile(Tile*);

	virtual void update(float);

	void render(int, int);

	bool getPlayer();

	float getPosX();

	float getPosY();

	void setAlpha(float);

	void resetAlpha();

protected:
	Tile* tile;
	STexture* spritesheet;
	SDL_Rect clip;
	int height;
	int width;
	//image offset (innate, calculated from top left corner)
	int offsetX;
	int offsetY;
	//position offset (from moving)
	float posX;
	float posY;
	int pass;
	int ghost;
	bool player;
	float alpha;
	bool uniqueAlpha;
};

#endif
