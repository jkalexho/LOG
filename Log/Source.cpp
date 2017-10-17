#include "Globals.h"
#include "Board.h"
#include "Actor.h"
#include "Moveto.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Timer.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

//Textures
STexture basic_tileset_texture("images/tilesets/basic tileset.png");
STexture cycle_spritesheet_texture("images/actors/Cycle Spritesheet.png");
STexture prison_tileset_texture("images/tilesets/prison tileset.png");
STexture move_tileset_texture("images/tilesets/move tileset.png");

//Tilesets
Tileset basic_tileset(&basic_tileset_texture, PASSABLE, 100, 50, 0);
Tileset prison_tileset(&prison_tileset_texture, PASSABLE, 100, 50, 0);

//Actors
Actor cycle(&cycle_spritesheet_texture, 400, SOUTH, 60, 100, 20, -60, PLAYER);

//Moveto
Moveto moveto(&move_tileset_texture);

Board gameBoard(&prison_tileset, 50, 50);

int zRound(float x) {
	if (x > 0) {
		x += 0.5;
	}
	else {
		x -= 0.5;
	}
	return (int)x;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("The Life of A Ghost", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	gameBoard.getTile(30, 30)->addOccupant(&cycle);

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	// Set Basic tileset texture renderer
	basic_tileset_texture.setRenderer(renderer);
	if (!basic_tileset_texture.loadFromFile())
	{
		printf("Failed to load basic tileset texture!\n");
		success = false;
	}
	// Set Prison tileset texture renderer
	prison_tileset_texture.setRenderer(renderer);
	if (!prison_tileset_texture.loadFromFile())
	{
		printf("Failed to load prison tileset texture!\n");
		success = false;
	}
	// Set cycle texture renderer
	cycle_spritesheet_texture.setRenderer(renderer);
	if (!cycle_spritesheet_texture.loadFromFile())
	{
		printf("Failed to load cycle spritesheet texture!\n");
		success = false;
	}
	// Set moveto texture renderer
	move_tileset_texture.setRenderer(renderer);
	if (!move_tileset_texture.loadFromFile())
	{
		printf("Failed to load move tileset texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	basic_tileset_texture.free();
	prison_tileset_texture.free();
	cycle_spritesheet_texture.free();
	move_tileset_texture.free();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Destroy game board

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			Timer stepTimer;

			float screenOffsetX = 0;
			float screenOffsetY = 0;
			int xCenter = 30;
			int yCenter = 30;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN) {
						int mouseX;
						int mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						float xclickScreen = mouseX - screenOffsetX - (SCREEN_WIDTH / 2);
						float yclickScreen = mouseY - screenOffsetY - (SCREEN_HEIGHT / 2);
						int xclickGrid = xCenter;
						int yclickGrid = yCenter;
						xclickGrid = xclickGrid - zRound(yclickScreen / 50 - xclickScreen / 100);
						yclickGrid = yclickGrid - zRound(yclickScreen / 50 + xclickScreen / 100);
						//printf("xclickGrid: %d, yclickGrid: %d \n", xclickGrid, yclickGrid);
						//if the selected tile is valid
						if (gameBoard.exists(xclickGrid, yclickGrid)) {
							//interact command
							if (e.button.button == SDL_BUTTON_LEFT) {

							}
							//move command
							else if (e.button.button == SDL_BUTTON_RIGHT) {
								cycle.move(gameBoard.getTile(xclickGrid, yclickGrid));
								moveto.reset();
								gameBoard.getTile(xclickGrid, yclickGrid)->addOccupant(&moveto);
							}
						}
					}
				}

				float timeStep = stepTimer.getTicks() / 1000.f;
				cycle.update(timeStep);

				screenOffsetX = -cycle.getPosX();

				screenOffsetY = -cycle.getPosY();

				xCenter = cycle.getTile()->getX();
				yCenter = cycle.getTile()->getY();

				//Clear screen
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				//Render game board
				gameBoard.render(renderer, xCenter, yCenter, SCREEN_WIDTH, SCREEN_HEIGHT, screenOffsetX, screenOffsetY, timeStep);

				stepTimer.start();

				//Update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}