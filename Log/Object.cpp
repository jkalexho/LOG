#include "Object.h"
#include "Globals.h"


Object::Object()
{
	spritesheet = NULL;
	tile = NULL;
	pass = IMPASSABLE;
	offsetX = 0;
	offsetY = 0;
	posX = 0.0;
	posY = 0.0;
	ghost = 0;
	player = 0;
	alpha = 1.0;
	uniqueAlpha = false;
}

Object::~Object()
{
}

void Object::update(float timeDiff) {
	return;
}

int Object::getGhost() {
	return ghost;
}

int Object::getPassability() {
	return pass;
}

Tile* Object::getTile() {
	return tile;
}

void Object::setTile(Tile* t) {
	tile = t;
}

void Object::changeTile(Tile* t) {
	tile->removeOccupant(this);
	t->addOccupant(this);
	tile = t;
}

void Object::setAlpha(float a) {
	alpha = a;
	uniqueAlpha = (alpha != spritesheet->getDefaultAlpha());
}

void Object::resetAlpha() {
	alpha = spritesheet->getDefaultAlpha();
	uniqueAlpha = false;
}

// x and y offsets are screen coordinates of the center of the square
void Object::render(int offx, int offy) {
	if (uniqueAlpha) {
		spritesheet->setAlpha(alpha);
	}
	spritesheet->render(offsetX + offx + (int)posX, offsetY + offy + (int)posY, &clip);
	if (uniqueAlpha) {
		spritesheet->resetAlpha();
	}
}

bool Object::getPlayer() {
	return player;
}

float Object::getPosX() {
	return posX;
}

float Object::getPosY() {
	return posY;
}
