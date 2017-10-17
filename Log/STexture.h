#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

#ifndef STEXTURE_H
#define STEXTURE_H

class STexture
{
public:
	STexture();

	STexture(string);

	STexture(SDL_Renderer*);

	STexture(string, SDL_Renderer*);

	STexture(string, float);

	~STexture();

	void setRenderer(SDL_Renderer*);

	void setURL(string);

	bool loadFromFile();

	void free();

	void render(int, int, SDL_Rect*);

	int getWidth();

	int getHeight();

	void setAlpha(float);

	void setDefaultAlpha(float);

	void resetAlpha();

	float getDefaultAlpha();

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	string url;
	int width;
	int height;
	float defaultAlpha;
};

#endif
