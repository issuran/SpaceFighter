#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <stdio.h>
#include <iostream>	

#pragma once

class ColliderComponent;

class Game {
public :
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

	bool running() { return isRunning; }

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window *window;
};