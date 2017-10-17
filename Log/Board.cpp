#include "Board.h"
#include "STexture.h"
#include "Globals.h"

Board::Board()
{
	board = NULL;
	width = 0;
	height = 0;
}

Board::Board(Tileset* t, int w, int h) {
	board = new Tile*[w*h];
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			board[i + j*w] = new Tile(i, j, t, NULL);
			if (i > 0) {
				board[i + j*w]->setNeighbor(SOUTHWEST, board[i-1 + j*w]);
				board[i - 1 + j*w]->setNeighbor(NORTHEAST, board[i + j*w]);
			}
			if (j > 0) {
				board[i + j*w]->setNeighbor(SOUTHEAST, board[i + (j - 1)*w]);
				board[i + (j - 1)*w]->setNeighbor(NORTHWEST, board[i + j*w]);
				if (i < w - 1) {
					board[i + j*w]->setNeighbor(EAST, board[i + 1 + (j - 1)*w]);
					board[i + 1 + (j - 1)*w]->setNeighbor(WEST, board[i + j*w]);
				}
				if (i > 0) {
					board[i + j*w]->setNeighbor(SOUTH, board[i - 1 + (j - 1)*w]);
					board[i - 1 + (j - 1)*w]->setNeighbor(NORTH, board[i + j*w]);
				}
			}
		}
	}
	width = w;
	height = h;
}


Board::~Board()
{
	delete[] board;
	board = NULL;
}

Tile* Board::getTile(int x, int y) {
	return board[x + y * width];
}

bool Board::exists(int x, int y) {
	return (x < width && x >= 0 && y >= 0 && y < height);
}

void Board::render(SDL_Renderer* r, int x, int y, int w, int h, float offsetX, float offsetY, float timeDifference) {
	int max = w / 100 + 3;
	int maxHeight = ((h - 25) / 100) * 2 + 4;
	int maxX;
	int maxY;
	int centerXPixel = (w - 100) / 2;
	int centerYPixel = (h - 50) / 2;
	Tile* maxTile;
	int currentX;
	int currentY;
	int currentXPixel;
	int currentYPixel;
	int offX = (int)offsetX;
	int offY = (int)offsetY;
	if (x + max + width * (y + max) < width * height - 1) {
		maxTile = board[x + (maxHeight - max) + width * (y + max)];
		currentX = x + (maxHeight - max);
		currentY = y + max;
	}
	else {
		maxTile = board[width * height - 1];
		currentX = width - 1;
		currentY = height - 1;
	}
	maxX = currentX;
	maxY = currentY;
	int min = x - max + (y - max) * width;
	while (currentX >= 0 && currentY >= 0 && currentX + currentY >= x + y - maxHeight) {
		currentXPixel = centerXPixel - 50 * ((currentY - y) - (currentX - x));
		currentYPixel = centerYPixel - 25 * ((currentX - x) + (currentY - y));
		maxTile->render(currentXPixel + offX, currentYPixel + offY);
		if (currentX < width - 1 && currentY > 0 && currentX < x + max) {
			currentX++;
			currentY--;
			maxTile = maxTile->getNeighbors()[EAST];
		}
		else {
			if (maxX > 0 && maxX > x - max) {
				currentY = maxY;
				currentX = --maxX;
			}
			else {
				currentY = --maxY;
				currentX = maxX;
			}
			if (currentY >= 0) {
				maxTile = board[currentX + width * currentY];
			}
		}
	}
	//Render objects
	centerXPixel = (w - 100) / 2;
	centerYPixel = (h - 50) / 2;
	if (x + max + width * (y + max) < width * height - 1) {
		maxTile = board[x + (maxHeight - max) + width * (y + max)];
		currentX = x + (maxHeight - max);
		currentY = y + max;
	}
	else {
		maxTile = board[width * height - 1];
		currentX = width - 1;
		currentY = height - 1;
	}
	maxX = currentX;
	maxY = currentY;
	while (currentX >= 0 && currentY >= 0 && currentX + currentY >= x + y - maxHeight) {
		currentXPixel = centerXPixel - 50 * ((currentY - y) - (currentX - x));
		currentYPixel = centerYPixel - 25 * ((currentX - x) + (currentY - y));
		if (maxTile->getOccupants() != NULL) {
			for (int f = 0; f < OCCUPANTS; f++) {
				if (maxTile->getOccupants()[f] != NULL) {
					if (!maxTile->getOccupants()[f]->getPlayer()) {
						maxTile->getOccupants()[f]->update(timeDifference);
					}
					if (maxTile->getOccupants()[f] != NULL) {
						maxTile->getOccupants()[f]->render(currentXPixel + offX, currentYPixel + offY);
					}
				}	
			}
		}
		if (currentX < width - 1 && currentY > 0 && currentX < x + max) {
			currentX++;
			currentY--;
			maxTile = maxTile->getNeighbors()[EAST];
		}
		else {
			if (maxX > 0 && maxX > x - max) {
				currentY = maxY;
				currentX = --maxX;
			}
			else {
				currentY = --maxY;
				currentX = maxX;
			}
			if (currentY >= 0) {
				maxTile = board[currentX + width * currentY];
			}
		}
	}
}
