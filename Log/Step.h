#include "Globals.h"
#include "Tile.h"

#ifndef STEP_H
#define STEP_H
class Step
{
public:
	Step();

	Step(Tile*, Tile*, int, float, float);

	Step(Step*, Tile*, Tile*, int, float, float);

	~Step();

	void setPrev(Step*);

	void setNext(Step*);

	Step* getPrev();

	Step* getNext();

	Tile* getStart();

	Tile* getEnd();

	int getDirection();

	float getHeuristic() const;

	float getdScore();

	float getxDisplacement();

	float getyDisplacement();

	bool completed();

	float update(float);

	float getProgress();

private:
	float progress;
	float distance;
	float xModifier;
	float yModifier;
	float xDisplacement;
	float yDisplacement;
	int direction;
	float hScore;
	float dScore;
	Tile* start;
	Tile* end;
	Step* prev;
	Step* next;
};
#endif
