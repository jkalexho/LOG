#include "Step.h"
#include "Globals.h"


Step::Step()
{
	progress = 0.0;
	direction = NULL;
	hScore = 0.0;
	dScore = 0.0;
	start = NULL;
	end = NULL;
	prev = NULL;
	next = NULL;
}

Step::Step(Tile* s, Tile* e, int d, float h, float dist) {
	progress = 0.0;
	direction = d;
	start = s;
	end = e;
	hScore = h;
	dScore = dist;
	prev = NULL;
	next = NULL;
	switch (direction) {
		case NORTHWEST:
			xModifier = -0.5;
			yModifier = -0.25;
			xDisplacement = 50;
			yDisplacement = 25;
			distance = 100;
			break;
		case NORTH: 
			xModifier = 0;
			yModifier = (float)(-0.3535);
			xDisplacement = 0;
			yDisplacement = 50;
			distance = (float)141.4;
			break;
		case NORTHEAST:
			xModifier = 0.5;
			yModifier = -0.25;
			xDisplacement = -50;
			yDisplacement = 25;
			distance = 100;
			break;
		case EAST:
			xModifier = (float)(0.7071);
			yModifier = 0;
			xDisplacement = -100;
			yDisplacement = 0;
			distance = (float)141.4;
			break;
		case SOUTHEAST:
			xModifier = (float)(0.5);
			yModifier = (float)(0.25);
			xDisplacement = -50;
			yDisplacement = -25;
			distance = 100;
			break;
		case SOUTH:
			xModifier = 0;
			yModifier = (float)(0.3535);
			xDisplacement = 0;
			yDisplacement = -50;
			distance = (float)141.4;
			break;
		case SOUTHWEST:
			xModifier = -0.5;
			yModifier = 0.25;
			xDisplacement = 50;
			yDisplacement = -25;
			distance = 100;
			break;
		case WEST:
			xModifier = -(float)(0.7071);
			yModifier = 0;
			xDisplacement = 100;
			yDisplacement = 0;
			distance = (float)141.4;
			break;
	}
}

Step::Step(Step* p, Tile* s, Tile* e, int d, float h, float dist) {
	progress = 0.0;
	direction = d;
	start = s;
	end = e;
	hScore = h;
	dScore = dist;
	prev = p;
	next = NULL;
	switch (direction) {
	case NORTHWEST:
		xModifier = -0.5;
		yModifier = -0.25;
		xDisplacement = 50;
		yDisplacement = 25;
		distance = 100;
		break;
	case NORTH:
		xModifier = 0;
		yModifier = (float)(-0.3535);
		xDisplacement = 0;
		yDisplacement = 50;
		distance = (float)141.4;
		break;
	case NORTHEAST:
		xModifier = 0.5;
		yModifier = -0.25;
		xDisplacement = -50;
		yDisplacement = 25;
		distance = 100;
		break;
	case EAST:
		xModifier = (float)(0.7071);
		yModifier = 0;
		xDisplacement = -100;
		yDisplacement = 0;
		distance = (float)141.4;
		break;
	case SOUTHEAST:
		xModifier = (float)(0.5);
		yModifier = (float)(0.25);
		xDisplacement = -50;
		yDisplacement = -25;
		distance = 100;
		break;
	case SOUTH:
		xModifier = 0;
		yModifier = (float)(0.3535);
		xDisplacement = 0;
		yDisplacement = -50;
		distance = (float)141.4;
		break;
	case SOUTHWEST:
		xModifier = -0.5;
		yModifier = 0.25;
		xDisplacement = 50;
		yDisplacement = -25;
		distance = 100;
		break;
	case WEST:
		xModifier = -(float)(0.7071);
		yModifier = 0;
		xDisplacement = 100;
		yDisplacement = 0;
		distance = (float)141.4;
		break;
	}
}

Step::~Step()
{
}

void Step::setPrev(Step* p) {
	prev = p;
}

void Step::setNext(Step* n) {
	next = n;
}

Step* Step::getPrev() {
	return prev;
}

Step* Step::getNext() {
	return next;
}

Tile* Step::getStart() {
	return start;
}

Tile* Step::getEnd() {
	return end;
}

float Step::getHeuristic() const {
	return hScore + dScore*0.95;
}

float Step::getdScore() {
	return dScore;
}

int Step::getDirection() {
	return direction;
}

float Step::getxDisplacement() {
	return xDisplacement;
}

float Step::getyDisplacement() {
	return yDisplacement;
}

float Step::update(float displacement) {
	if (displacement + progress > distance) {
		xDisplacement = 0.0;
		yDisplacement = 0.0;
		progress += displacement;
		return displacement + progress - distance;
	}
	else {
		xDisplacement += (displacement * xModifier);
		yDisplacement += (displacement * yModifier);
		progress += displacement;
		return 0;
	}
}

bool Step::completed() {
	return progress >= distance;
}

float Step::getProgress() {
	return progress;
}
