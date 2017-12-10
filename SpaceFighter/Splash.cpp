#include "Splash.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <SDL_mixer.h>

Mix_Music *splash_music = NULL;

SDL_Renderer* Splash::renderer = nullptr;

SDL_Event Splash::event;

int cont = 0;

//The surface_splash contained by the window 
SDL_Surface *surface_splash = NULL;

SDL_Texture *img = NULL;
SDL_Texture *img1 = NULL;
SDL_Texture *img2 = NULL;
SDL_Texture *img3 = NULL;
SDL_Texture *img4 = NULL;
SDL_Rect tex_splash;

Splash::Splash()
{}

Splash::~Splash()
{}

void Splash::init(SDL_Window *Window, SDL_Renderer *Renderer, SDL_Surface *Surface)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window_splash = Window;

		surface_splash = Surface;

		renderer = Renderer;

		isRunning = true;

		// load our image
		img = IMG_LoadTexture(renderer, "assets/splash.png");
		img1 = IMG_LoadTexture(renderer, "assets/splash1.png");
		img2 = IMG_LoadTexture(renderer, "assets/splash2.png");
		img3 = IMG_LoadTexture(renderer, "assets/splash3.png");
		img4 = IMG_LoadTexture(renderer, "assets/splash4.png");

		int w, h; // texture width & height
		SDL_QueryTexture(img2, NULL, NULL, &w, &h); // get the width and height of the texture
		tex_splash.x = 0; 
		tex_splash.y = 0;
		tex_splash.w = w; 
		tex_splash.h = h;

		//Load music 		
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		splash_music = Mix_LoadMUS("sounds/splash.mid");
		Mix_PlayMusic(splash_music, 1);
	}
	else {
		isRunning = false;
	}
}

void Splash::handleEvents()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN) {
		switch (Splash::event.key.keysym.sym)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDLK_KP_ENTER:
			isRunning = false;
			break;
		case SDLK_SPACE:
			isRunning = false;
			break;
		default:
			break;
		}
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
	if (cont < 95) SDL_RenderCopy(renderer, img, NULL, &tex_splash);

	else if (cont < 330) SDL_RenderCopy(renderer, img1, NULL, &tex_splash);

	else if (cont < 565) SDL_RenderCopy(renderer, img2, NULL, &tex_splash);

	else if (cont < 800) SDL_RenderCopy(renderer, img3, NULL, &tex_splash);

	else SDL_RenderCopy(renderer, img4, NULL, &tex_splash);

	SDL_RenderPresent(renderer);
}

void Splash::clean()
{
	SDL_DestroyWindow(window_splash);
	SDL_DestroyRenderer(renderer);	
	SDL_DestroyTexture(img);
	SDL_DestroyTexture(img1);
	SDL_DestroyTexture(img2);
	SDL_DestroyTexture(img3);
	SDL_DestroyTexture(img4);
	SDL_Quit();
	std::cout << "Splash Cleaned" << std::endl;
}