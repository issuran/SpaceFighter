#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <stdio.h>
#include <iostream>	

#pragma once

class GameOver {
public:
	GameOver();
	~GameOver();

	void init(SDL_Window *Window, SDL_Renderer* Renderer, SDL_Surface* Surface);

	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;

	bool running() { return isRunning; }

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window *window_over;
};