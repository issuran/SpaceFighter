#include "MainMenu.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <SDL_mixer.h>

Mix_Music *main_music = NULL;

SDL_Renderer* MainMenu::renderer = nullptr;

SDL_Event MainMenu::event;

bool isMainMenu = false;

//The surface_main contained by the window 
SDL_Surface *surface_main = NULL;

SDL_Texture *img_mainmenu = NULL;
SDL_Rect tex_main;

MainMenu::MainMenu()
{}

MainMenu::~MainMenu()
{}

void MainMenu::init(SDL_Window *Window, SDL_Renderer *Renderer, SDL_Surface *Surface)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window_menu = Window;

		surface_main = Surface;

		renderer = Renderer;

		isRunning = true;

		// load our image
		img_mainmenu = IMG_LoadTexture(renderer, "assets/mainmenu.png");

		int w, h; // texture width & height
		SDL_QueryTexture(img_mainmenu, NULL, NULL, &w, &h); // get the width and height of the texture
		tex_main.x = 0;
		tex_main.y = 0;
		tex_main.w = w;
		tex_main.h = h;

		//Load music 		
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		main_music = Mix_LoadMUS("sounds/menu_x.mid");
		Mix_PlayMusic(main_music, -1);
	}
	else {
		isRunning = false;
	}
}

void MainMenu::handleEvents()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN) {
		switch (MainMenu::event.key.keysym.sym)
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

void MainMenu::update()
{
}

void MainMenu::render()
{
	SDL_RenderClear(renderer);
	
	SDL_RenderCopy(renderer, img_mainmenu, NULL, &tex_main);

	SDL_RenderPresent(renderer);
}

void MainMenu::clean()
{
	SDL_DestroyWindow(window_menu);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(img_mainmenu);
	SDL_Quit();
	std::cout << "MainMenu Cleaned" << std::endl;
}