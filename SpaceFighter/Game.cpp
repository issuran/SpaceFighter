#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <SDL_mixer.h>

Mix_Music *gMusic = NULL;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& screenBoundaryLeft(manager.addEntity());
auto& screenBoundaryTop(manager.addEntity());
auto& screenBoundaryDown(manager.addEntity());
auto& screenBoundaryRight(manager.addEntity());
auto& background(manager.addEntity());

//The background scrolling offset 
int scrollingOffset = 0;
//SDL_Surface* background;

enum groupLabels : std::size_t{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupBackground
};

SDL_Texture *texture;

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

		//Map::LoadMap("assets/p16x16.map", 16, 16);

		background.addComponent<TransformComponent>(0.0f, 0.0f, 640, 800, 1);
		background.addComponent<BackgroundComponent>("assets/bg.png");
		background.addGroup(groupBackground);

		player.addComponent<TransformComponent>(50.0f, 250.0f, 36, 106, 1);
		player.addComponent<SpriteComponent>("assets/nave_sprite.png", 4, 100);
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");
		player.addGroup(groupPlayers);

		//Load music 
		int resultrr = 0;
		int flagsd = MIX_INIT_MP3;
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		gMusic = Mix_LoadMUS( "sounds/game.mid" );
		Mix_PlayMusic(gMusic, 1);

		screenBoundaryLeft.addComponent<TransformComponent>(0.0f, 0.0f, 640, 0, 1);
		screenBoundaryLeft.addComponent<SpriteComponent>("assets/dirt.png");
		screenBoundaryLeft.addComponent<ColliderComponent>("boundary left");
		screenBoundaryLeft.addGroup(groupMap);

		screenBoundaryTop.addComponent<TransformComponent>(0.0f, 0.0f, 0, 800, 1);
		screenBoundaryTop.addComponent<SpriteComponent>("assets/dirt.png");
		screenBoundaryTop.addComponent<ColliderComponent>("boundary top");
		screenBoundaryTop.addGroup(groupMap);
		
		screenBoundaryDown.addComponent<TransformComponent>(0, 640, 0, 800, 1);
		screenBoundaryDown.addComponent<SpriteComponent>("assets/dirt.png");
		screenBoundaryDown.addComponent<ColliderComponent>("boundary down");
		screenBoundaryDown.addGroup(groupMap);
		
		screenBoundaryRight.addComponent<TransformComponent>(800, 0, 640, 0, 1);
		screenBoundaryRight.addComponent<SpriteComponent>("assets/dirt.png");
		screenBoundaryRight.addComponent<ColliderComponent>("boundary right");
		screenBoundaryRight.addGroup(groupMap);


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

	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryLeft.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().velocity * -2;

		std::cout << "Boundary Hit!" << std::endl;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryTop.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().velocity * -1;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryDown.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().velocity * -1;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryRight.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().velocity * -1;
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& backgrounds(manager.getGroup(groupBackground));

void Game::render() 
{
	SDL_RenderClear(renderer);

	for (auto& b : backgrounds) {
		b->draw();
	}

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& e : enemies) {
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}