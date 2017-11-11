#pragma once
#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:

	static const int rows = 20;
	static const int columns = 25;

	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};
