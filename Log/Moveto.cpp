#include "Moveto.h"



Moveto::Moveto()
{
	spritesheet = NULL;
	tile = NULL;
	pass = PASSABLE;
	width = 100;
	height = 50;
	offsetX = 0;
	offsetY = 0;
	posX = 0.0;
	posY = 0.0;
	ghost = MOVETO;
	player = false;
	frame = 0;
	animProgress = 0.0;
	alpha = 1.0;
	uniqueAlpha = false;
}

Moveto::Moveto(STexture* s) {
	spritesheet = s;
	width = 100;
	height = 50;
	offsetX = 0;
	offsetY = 0;
	clip = { 0, 0, width, height };
	pass = PASSABLE;
	ghost = MOVETO;
	player = false;
	posX = 0.0;
	posY = 0.0;
	frame = 0;
	animProgress = 0.0;
	alpha = 1.0;
	uniqueAlpha = false;
}

Moveto::~Moveto()
{
}

void Moveto::update(float timeDifference) {
	animProgress += timeDifference;
	clip = { ((int)(animProgress * 20)) * width, 0, width, height };
	if (animProgress > 0.5) {
		reset();
	}
}

void Moveto::reset() {
	if (tile != NULL) {
		tile->removeOccupant(this);
	}
	animProgress = 0.0;
}
