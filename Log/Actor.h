#include "Object.h"
#include "Globals.h"
#include "Step.h"

#ifndef ACTOR_H
#define ACTOR_H
class Actor :
	public Object
{
public:
	Actor();

	Actor(STexture*, Tile*, float, int, int, int, int, int, int);

	Actor(STexture*, float, int, int, int, int, int, int);

	~Actor();

	float getPosX();

	float getPosY();

	Step* getPath(Tile*);

	bool tileTestPass(Tile*);

	void update(float);

	void move(Tile*);

private:
	Step* nextStep;
	Step* currentStep;
	Tile* destination;
	float velocity;
	int direction;
	int action;
	int frame;
	float animProgress;
};
#endif

