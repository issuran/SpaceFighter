#include "Splash.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <SDL_mixer.h>

Mix_Music *sMusic = NULL;

SDL_Renderer* Splash::renderer = nullptr;

SDL_Event Splash::event;

int cont = 0;

//The surface contained by the window 
SDL_Surface* gScreenSurface = NULL;

SDL_Texture *img = NULL;
SDL_Texture *img2 = NULL;
SDL_Rect texr;

Splash::Splash()
{}

Splash::~Splash()
{}

void Splash::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		//Get window surface 
		gScreenSurface = SDL_GetWindowSurface(window);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

		// load our image
		img = IMG_LoadTexture(renderer, "assets/splash.png");
		img2 = IMG_LoadTexture(renderer, "assets/splash2.png");

		int w, h; // texture width & height
		SDL_QueryTexture(img2, NULL, NULL, &w, &h); // get the width and height of the texture
		texr.x = 0; 
		texr.y = 0;
		texr.w = w; 
		texr.h = h;

		//Load music 		
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		sMusic = Mix_LoadMUS("sounds/open1.mid");
		Mix_PlayMusic(sMusic, 1);

	}
	else {
		isRunning = false;
	}
}

void Splash::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Splash::update()
{
	if (cont > 600) isRunning = false;
	cont++;
	std::cout << cont << std::endl;
}

void Splash::render()
{
	SDL_RenderClear(renderer);

	// copy the texture to the rendering context
	if (cont < 300) SDL_RenderCopy(renderer, img, NULL, &texr);

	else SDL_RenderCopy(renderer, img2, NULL, &texr);

	SDL_RenderPresent(renderer);
}

void Splash::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Splash Cleaned" << std::endl;
}