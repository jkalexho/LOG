#include <string>
#include "STexture.h"

using namespace std;

#ifndef TILESET_H
#define TILESET_H
class Tileset
{
public:
	Tileset();
	Tileset(STexture*, int, int, int, int);
	~Tileset();
	int getWidth();
	int getHeight();
	//int getOffsetX();
	int getOffsetY();
	int getPassability();
	STexture* getTexture();
private:
	STexture* texture;
	int pass;
	int width;
	int height;
	//int offsetX;
	int offsetY;
};
#endif
