#include "GameOver.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <SDL_mixer.h>

Mix_Music *gameover_music = NULL;

SDL_Renderer* GameOver::renderer = nullptr;

SDL_Event GameOver::event;

bool isGameOver = false;

SDL_Texture *img_gameover = NULL;
SDL_Rect tex_over;

GameOver::GameOver()
{}

GameOver::~GameOver()
{}

void GameOver::init(SDL_Window *Window, SDL_Renderer *Renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window_over = Window;

		renderer = Renderer;

		isRunning = true;

		// load our image
		img_gameover = IMG_LoadTexture(renderer, "assets/gameover.png");

		int w, h; // texture width & height
		SDL_QueryTexture(img_gameover, NULL, NULL, &w, &h); // get the width and height of the texture
		tex_over.x = 0;
		tex_over.y = 0;
		tex_over.w = w;
		tex_over.h = h;

		//Load music 		
		Mix_HaltMusic();
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		gameover_music = Mix_LoadMUS("sounds/game_over.mid");
		Mix_PlayMusic(gameover_music, -1);
	}
	else {
		isRunning = false;
	}
}

void GameOver::handleEvents()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN) {
		switch (GameOver::event.key.keysym.sym)
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

void GameOver::update()
{
}

void GameOver::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, img_gameover, NULL, &tex_over);

	SDL_RenderPresent(renderer);
}

void GameOver::clean()
{
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(img_gameover);
	Mix_HaltMusic();
	std::cout << "Game Over Cleaned" << std::endl;
}