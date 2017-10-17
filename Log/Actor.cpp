#include "Actor.h"
#include <queue>
#include <vector>


struct CompareStep {
	bool operator() (const Step* a, const Step* b) const {
		//printf("step a: %f, step b: %f \n", a->getHeuristic(), b->getHeuristic());
		return (a->getHeuristic() > b->getHeuristic());
	}
};


Actor::Actor()
{
	tile = NULL;
	spritesheet = NULL;
	velocity = 0;
	direction = 0;
	width = 0;
	height = 0;
	offsetX = 0;
	offsetY = 0;
	ghost = 0;
	action = 0;
	frame = 0;
	animProgress = 0.0;
	posX = 0.0;
	posY = 0.0;
	player = false;
	nextStep = NULL;
	pass = IMPASSABLE;
	alpha = 1.0;
}

Actor::Actor(STexture* s, float v, int d, int w, int h, int offx, int offy, int g) {
	tile = NULL;
	spritesheet = s;
	velocity = v;
	direction = d;
	width = w;
	height = h;
	offsetX = offx;
	offsetY = offy;
	ghost = g;
	if (g > PHYSICAL) {
		pass = PASSABLE;
	}
	else {
		pass = OCCUPIED;
	}
	if (g == PLAYER) {
		player = true;
	}
	clip = { 0, direction * h, w, h };
	action = IDLE;
	frame = 0;
	animProgress = 0.0;
	posX = 0.0;
	posY = 0.0;
	nextStep = NULL;
	currentStep = NULL;
	alpha = 1.0;
}

Actor::Actor(STexture* s, Tile* t, float v, int d, int w, int h, int offx, int offy, int g) {
	tile = t;
	spritesheet = s;
	velocity = v;
	direction = d;
	width = w;
	height = h;
	offsetX = offx;
	offsetY = offy;
	ghost = g;
	if (g > PHYSICAL) {
		pass = PASSABLE;
	}
	else {
		pass = OCCUPIED;
	}
	if (g == PLAYER) {
		player = true;
	}
	clip = { 0, direction * h, w, h };
	action = IDLE;
	frame = 0;
	posX = 0.0;
	posY = 0.0;
	nextStep = NULL;
	currentStep = NULL;
	alpha = 1.0;
}


Actor::~Actor()
{
}

float Actor::getPosX() {
	return posX;
}

float Actor::getPosY() {
	return posY;
}

bool Actor::tileTestPass(Tile* t) {
	int pass = t->getPassability();
	if (ghost == PHYSICAL) {
		if ((pass == FORCEFIELD || pass == PASSABLE) && t->getOccupants()[PHYSICAL] == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (pass == PASSABLE || pass == WALL) {
			if (t->getOccupants()[GHOST] == NULL && ghost == GHOST) {
				return true;
			}
			else if (ghost == PLAYER) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
}

Step* Actor::getPath(Tile* end) {
	// in case no path exists
	destination = end;
	int stepLimit = 47;
	bool finish = false;
	bool passable = false;
	priority_queue<Step*, vector<Step*>, CompareStep> pathSpace;
	priority_queue<Step*, vector<Step*>, CompareStep> bestPath;
	int endX = end->getX();
	int endY = end->getY();
	int nextX;
	int nextY;
	float dScore;
	float hScore;
	int d_max;
	int d_min;
	Tile *curTile;
	Tile *nextTile;
	Step *curStep = new Step();
	Step *tempStep = new Step();
	curTile = tile;
	for (int i = NORTHWEST; i <= WEST; i++) {
		nextTile = curTile->getNeighbors()[i];
		passable = false;
		//if tile exists and is passable
		if (nextTile != NULL && tileTestPass(nextTile)) {
			if (i % 2 == 0) {
				passable = true;
			}
			else {
				if (tileTestPass(curTile->getNeighbors()[(i + 7) % 8]) && tileTestPass(curTile->getNeighbors()[(i + 1) % 8])) {
					passable = true;
				}
			}
		}
		if (passable) {
			if (i % 2 == 0) {
				dScore = (float)1.0;
			}
			else {
				dScore = (float)1.4;
			}
			nextX = nextTile->getX();
			nextY = nextTile->getY();
			d_max = max(abs(endX - nextX), abs(endY - nextY));
			d_min = min(abs(endX - nextX), abs(endY - nextY));
			hScore = (float)1.4 * d_min + d_max - d_min;
			pathSpace.push(new Step(curTile, nextTile, i, hScore, dScore));
		}
	}
	while (stepLimit > 0 && !finish) {
		stepLimit--;
		curStep = pathSpace.top();
		bestPath.push(pathSpace.top());
		pathSpace.pop();
		dScore = curStep->getdScore();
		curTile = curStep->getEnd();
		//if not finished
		if (curTile != end) {
			//check all directions...
			for (int i = NORTHWEST; i <= WEST; i++) {
				//...except backwards
				if (i != (curStep->getDirection() + 4) % 8) {
					dScore = curStep->getdScore();
					nextTile = curTile->getNeighbors()[i];
					//verify if step can be taken
					passable = false;
					if (nextTile != NULL && tileTestPass(nextTile)) {
						if (i % 2 == 0) {
							passable = true;
						}
						else {
							if (tileTestPass(curTile->getNeighbors()[(i + 7) % 8]) && tileTestPass(curTile->getNeighbors()[(i + 1) % 8])) {
								passable = true;
							}
						}
					}
					//if the step can be taken
					if (passable) {
						if (i % 2 == 0) {
							dScore = dScore + (float)1.0;
						}
						else {
							dScore = dScore + (float)1.414;
						}
						nextX = nextTile->getX();
						nextY = nextTile->getY();
						d_max = max(abs(endX - nextX), abs(endY - nextY));
						d_min = min(abs(endX - nextX), abs(endY - nextY));
						hScore = (float)1.414 * d_min + d_max - d_min;
						pathSpace.push(new Step(curStep, curTile, nextTile, i, hScore, dScore));
					}
				}
			}
		}
		//finish
		else {
			finish = true;
		}
	}
	if (!finish) {
		curStep = bestPath.top();
	}
	while (curStep->getPrev() != NULL) {
		curStep->getPrev()->setNext(curStep);
		curStep = curStep->getPrev();
	}
	while (!bestPath.empty()) {
		bestPath.pop();
	}
	while (!pathSpace.empty()) {
		pathSpace.pop();
	}
	return curStep;
}

void Actor::move(Tile* d) {
	if (d != tile) {
		nextStep = getPath(d);
		action = MOVE;
	}
}

void Actor::update(float timeDifference) {
	if (action == IDLE) {
		clip = { 0, direction * height, width, height };
	}
	else if (action == MOVE) {
		if (currentStep == NULL) {
			if (nextStep == NULL) {
				action = IDLE;
				clip = { 0, direction * height, width, height };
			}
			else {
				currentStep = nextStep;
				nextStep = currentStep->getNext();
				direction = currentStep->getDirection();
			}
		}
		//if the next tile hasn't changed passability
		if (tile != currentStep->getEnd() && tileTestPass(currentStep->getEnd())) {
			changeTile(currentStep->getEnd());
		}
		float extra = currentStep->update(timeDifference * velocity);
		//if leftover distance not travelled yet
		while (extra > 0 && nextStep != NULL) {
			delete currentStep;
			if (!tileTestPass(nextStep->getEnd())) {
				nextStep = getPath(destination);
			}
			currentStep = nextStep;
			nextStep = currentStep->getNext();
			direction = currentStep->getDirection();
			changeTile(currentStep->getEnd());
			extra = currentStep->update(extra);
		}
		if (currentStep->completed() && nextStep == NULL) {
			action = IDLE;
			clip = { 0, direction * height, width, height };
		}
		else {
			posX = currentStep->getxDisplacement();
			posY = currentStep->getyDisplacement();
			animProgress = animProgress + timeDifference;
			if (animProgress > 0.5) {
				animProgress -= (float)0.5;
			}
			// animation updates every 1000 / 12 ms, hence the animProgress * 12.
			clip = { ((int)(animProgress * 12) + 1) * width, direction * height, width, height };
		}
	}
	else {
		return;
	}
}
