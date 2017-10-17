#include "Tileset.h"



Tileset::Tileset()
{
	texture = NULL;
	pass = NULL;
	width = NULL;
	height = NULL;
}

Tileset::Tileset(STexture* t, int p, int w, int h, int o) {
	this->texture = t;
	this->pass = p;
	this->width = w;
	this->height = h;
	this->offsetY = o;
}


Tileset::~Tileset()
{
}

int Tileset::getPassability() {
	return pass;
}

int Tileset::getWidth() {
	return width;
}

int Tileset::getHeight() {
	return height;
}

STexture* Tileset::getTexture() {
	return texture;
}

int Tileset::getOffsetY() {
	return offsetY;
}
