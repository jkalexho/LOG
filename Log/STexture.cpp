#include "STexture.h"



STexture::STexture()
{
	texture = NULL;
	width = 0;
	height = 0;
	renderer = NULL;
	url = "";
	defaultAlpha = 1.0;
}

STexture::STexture(string u) {
	texture = NULL;
	width = 0;
	height = 0;
	renderer = NULL;
	url = u;
	defaultAlpha = 1.0;
}

STexture::STexture(string u, float a) {
	texture = NULL;
	width = 0;
	height = 0;
	renderer = NULL;
	url = u;
	defaultAlpha = a;
}

STexture::STexture(SDL_Renderer* r) {
	texture = NULL;
	width = 0;
	height = 0;
	renderer = r;
	url = "";
	defaultAlpha = 1.0;
}

STexture::STexture(string u, SDL_Renderer* r) {
	texture = NULL;
	width = 0;
	height = 0;
	renderer = r;
	url = u;
	defaultAlpha = 1.0;
}

STexture::~STexture()
{
	free();
}

void STexture::setRenderer(SDL_Renderer* r) {
	renderer = r;
}

void STexture::setURL(string u) {
	url = u;
}

bool STexture::loadFromFile() {

	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(url.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", url.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", url.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	resetAlpha();
	return texture != NULL;
}

void STexture::free() {
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void STexture::setAlpha(float a) {
	int alpha = (int)(a * 255);
	SDL_SetTextureAlphaMod(texture, alpha);
}

float STexture::getDefaultAlpha() {
	return defaultAlpha;
}

void STexture::setDefaultAlpha(float a) {
	defaultAlpha = a;
}

void STexture::resetAlpha() {
	SDL_SetTextureAlphaMod(texture, defaultAlpha * 255);
}

void STexture::render(int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int STexture::getWidth() {
	return width;
}

int STexture::getHeight() {
	return height;
}
