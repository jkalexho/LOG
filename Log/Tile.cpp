//Tile class

#include "Tile.h"
#include "Object.h"


Tile::Tile()
{
	x = 0;
	y = 0;
	t = NULL;
	pass = IMPASSABLE;
	for (int i = 0; i < 4; i++) {
		occupants[i] = NULL;
	}
	for (int i = 0; i < 8; i++) {
		neighbors[i] = NULL;
	}
}

Tile::Tile(int x, int y, Tileset* t, Object* o) {
	setX(x);
	setY(y);
	setTileset(t);
	pass = t->getPassability();
	if (o) {
		addOccupant(o);
	}
}

Tile::Tile(Tileset* t) {
	x = 0;
	y = 0;
	setTileset(t);
	pass = t->getPassability();
}


Tile::~Tile()
{
}

void Tile::setX(int num) {
	x = num;
}

void Tile::setY(int num) {
	y = num;
}

int Tile::getPassability() {
	return pass;
}

void Tile::addOccupant(Object* o) {
	o->setTile(this);
	int x = o->getGhost();
	occupants[x] = o;
}

void Tile::removeOccupant(Object* o) {
	int x = o->getGhost();
	occupants[x] = NULL;
	o->setTile(NULL);
}

void Tile::setTileset(Tileset* tileset) {
	t = tileset;
	int random = x | y;
	random = random + x % (y + 1); 
	random = random % 47;
	random = (random | (x + y)) % TILESET_SIZE;
	offsetX = random * tileset->getWidth();
	pass = tileset->getPassability();
	clip = { offsetX, 0, getWidth(), getHeight() };
}

void Tile::render(int offsetX, int offsetY) {
	t->getTexture()->render(offsetX, offsetY + t->getOffsetY(), &clip);
}

void Tile::setNeighbor(int direction, Tile* neighbor) {
	neighbors[direction] = neighbor;
}

int Tile::getWidth() {
	return t->getWidth();
}

int Tile::getHeight() {
	return t->getHeight();
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}

Tile** Tile::getNeighbors() {
	return neighbors;
}

Tileset* Tile::getTileset() {
	return t;
}

Object** Tile::getOccupants() {
	return occupants;
}
