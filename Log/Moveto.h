#include "Globals.h"
#include "Object.h"

#ifndef MOVETO_H
#define MOVETO_H
class Moveto :
	public Object
{
public:
	Moveto();

	Moveto(STexture*);

	~Moveto();

	void update(float);

	void reset();

private:
	int frame;
	float animProgress;
};
#endif
