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

bool isMainMenu = false;

//The surface contained by the window 
SDL_Surface *surface = NULL;

SDL_Texture *img = NULL;
SDL_Texture *img1 = NULL;
SDL_Texture *img2 = NULL;
SDL_Texture *img3 = NULL;
SDL_Texture *img4 = NULL;
SDL_Rect texr;

Splash::Splash()
{}

Splash::~Splash()
{}

void Splash::init(SDL_Window *Window, SDL_Renderer *Renderer, SDL_Surface *Surface)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = Window;

		surface = Surface;

		renderer = Renderer;

		isRunning = true;

		// load our image
		img = IMG_LoadTexture(renderer, "assets/splash.png");
		img1 = IMG_LoadTexture(renderer, "assets/splash1.png");
		img2 = IMG_LoadTexture(renderer, "assets/splash2.png");
		img3 = IMG_LoadTexture(renderer, "assets/splash3.png");
		img4 = IMG_LoadTexture(renderer, "assets/mainmenu.png");

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
	if (cont > 1000) isRunning = false;
	cont++;
	std::cout << cont << std::endl;
}

void Splash::render()
{
	SDL_RenderClear(renderer);

	// copy the texture to the rendering context
	if (cont < 95) SDL_RenderCopy(renderer, img, NULL, &texr);

	else if (cont < 330) SDL_RenderCopy(renderer, img1, NULL, &texr);

	else if (cont < 565) SDL_RenderCopy(renderer, img2, NULL, &texr);

	else if (cont < 800) SDL_RenderCopy(renderer, img3, NULL, &texr);

	else SDL_RenderCopy(renderer, img4, NULL, &texr);

	SDL_RenderPresent(renderer);
}

void Splash::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);	
	SDL_DestroyTexture(img);
	SDL_DestroyTexture(img1);
	SDL_DestroyTexture(img2);
	SDL_DestroyTexture(img3);
	SDL_DestroyTexture(img4);
	SDL_Quit();
	std::cout << "Splash Cleaned" << std::endl;
}