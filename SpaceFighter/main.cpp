#include "SDL.h"
#include "Game.h"
#include "Splash.h"

Game *game = nullptr;
Splash *splash = nullptr;

int main(int argc, char *argv[]) {
	/*while (game is running) {
		handle any user input
		update all object eg. positions etc.
		render changes to the display

	}*/

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	splash = new Splash();
	game = new Game();

	splash->init("Splash Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (splash->running())
	{

		frameStart = SDL_GetTicks();

		splash->update();
		splash->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->init("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;

}