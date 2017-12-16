#include "SDL.h"
#include "Game.h"
#include "Splash.h"
#include "MainMenu.h"
#include "GameOver.h"

Game *game = nullptr;
Splash *splash = nullptr;
MainMenu *main_menu = nullptr;
GameOver *game_over = nullptr;

SDL_Window *window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Surface* surfaces = nullptr;


SDL_Window* createWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	return SDL_CreateWindow(title, xpos, ypos, width, height, flags);
}

SDL_Renderer* createRenderer(SDL_Window *window) {
	return SDL_CreateRenderer(window, -1, 0);
}

SDL_Surface* createSurface(SDL_Window *window) {
	return SDL_GetWindowSurface(window);
}

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
	main_menu = new MainMenu();
	game = new Game();
	game_over = new GameOver();

	bool isRunningGame = true;

	SDL_Init(SDL_INIT_EVERYTHING);

	//Create game window
	window = createWindow("Splash Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	if (window)
	{
		std::cout << "Window created!" << std::endl;
	}

	renderer = createRenderer(window);

	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		std::cout << "Renderer created!" << std::endl;
	}

	surfaces = createSurface(window);

	splash->init(window, renderer, surfaces);

	while (splash->running())
	{

		frameStart = SDL_GetTicks();

		splash->update();
		splash->render();
		splash->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	SDL_SetWindowTitle(window, "Main Menu Screen");

	main_menu->init(window, renderer, surfaces);

	while (main_menu->running())
	{

		frameStart = SDL_GetTicks();

		main_menu->update();
		main_menu->render();
		main_menu->handleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	while (isRunningGame) {
		SDL_SetWindowTitle(window, "Game Screen");

		game->init(window, renderer);

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

		SDL_SetWindowTitle(window, "Game Over Screen");

		game_over->init(window, renderer, surfaces);

		while (game_over->running())
		{

			frameStart = SDL_GetTicks();

			game_over->update();
			game_over->render();
			game_over->handleEvents();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}

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


		//Create game window
		window = createWindow("Splash Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

		renderer = createRenderer(window);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		surfaces = createSurface(window);
	}

	game_over->clean();

	return 0;

}
