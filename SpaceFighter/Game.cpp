#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

auto& player(manager.addEntity());
auto& ground(manager.addEntity());

Game::Game() 
{}

Game::~Game() 
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
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

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

		map = new Map();

		player.addComponent<TransformComponent>(2);
		player.addComponent<SpriteComponent>("assets/nave.png");
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");

		ground.addComponent<TransformComponent>(300.0f, 300.0f, 800, 32, 1);
		ground.addComponent<SpriteComponent>("assets/dirt.png");
		ground.addComponent<ColliderComponent>("wall");


	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents() 
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

void Game::update() 
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		ground.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().scale = 1;
		std::cout << "Ground Hit!" << std::endl;
	}
}

void Game::render() 
{
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	map->DrawMap();
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}