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
auto& enemy(manager.addEntity());
auto& enemy_toxic(manager.addEntity());
auto& enemy_fury(manager.addEntity());
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

void Game::init(SDL_Window *Window, SDL_Renderer* Renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = Window;

		renderer = Renderer;

		isRunning = true;
		
		//map = new Map();

		//Map::LoadMap("assets/p16x16.map", 16, 16);

		background.addComponent<TransformComponent>(0.0f, 0.0f, 640, 800, 1);
		background.addComponent<BackgroundComponent>("assets/bg.png");
		background.addGroup(groupBackground);

		player.addComponent<TransformComponent>(50.0f, 250.0f, 36, 106, 1);
		player.addComponent<SpriteComponent>("assets/nave_sprite.png", 4, 100);
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");
		player.addGroup(groupPlayers);

		enemy.addComponent<TransformComponent>(640.0f, 350.0f, 55, 56, 1);
		enemy.addComponent<SpriteComponent>("assets/alienship.png");
		enemy.addComponent<ColliderComponent>("enemy");		
		enemy.addComponent<Alien>();
		enemy.addGroup(groupEnemies);

		enemy_toxic.addComponent<TransformComponent>(640.0f, 150.0f, 55, 56, 1);
		enemy_toxic.addComponent<SpriteComponent>("assets/alientoxicship.png");
		enemy_toxic.addComponent<ColliderComponent>("enemy");
		enemy_toxic.addComponent<AlienToxic>();
		enemy_toxic.addGroup(groupEnemies);

		enemy_fury.addComponent<TransformComponent>(640.0f, 550.0f, 55, 56, 1);
		enemy_fury.addComponent<SpriteComponent>("assets/alienfuryship.png");
		enemy_fury.addComponent<ColliderComponent>("enemy");
		enemy_fury.addComponent<AlienFury>();
		enemy_fury.addGroup(groupEnemies);

		//Load music 
		int resultrr = 0;
		int flagsd = MIX_INIT_MP3;
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		gMusic = Mix_LoadMUS( "sounds/game_x2.mid" );
		Mix_PlayMusic(gMusic, -1);

		screenBoundaryLeft.addComponent<TransformComponent>(0.0f, 0.0f, 640, 0, 1);
		screenBoundaryLeft.addComponent<ColliderComponent>("boundary left");
		screenBoundaryLeft.addGroup(groupMap);

		screenBoundaryTop.addComponent<TransformComponent>(0.0f, 0.0f, 0, 800, 1);
		screenBoundaryTop.addComponent<ColliderComponent>("boundary top");
		screenBoundaryTop.addGroup(groupMap);
		
		screenBoundaryDown.addComponent<TransformComponent>(0, 640, 0, 800, 1);
		screenBoundaryDown.addComponent<ColliderComponent>("boundary down");
		screenBoundaryDown.addGroup(groupMap);
		
		screenBoundaryRight.addComponent<TransformComponent>(800, 0, 640, 0, 1);
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

	enemy_fury.getComponent<AlienFury>().update(player.getComponent<TransformComponent>().position.y);

	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryLeft.getComponent<ColliderComponent>().collider))
	{
		if (player.getComponent<TransformComponent>().position.x <= 0) {
			player.getComponent<TransformComponent>().position.x += 10;
		}

		
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryTop.getComponent<ColliderComponent>().collider)) {
		if (player.getComponent<TransformComponent>().position.y <= 0) {
			player.getComponent<TransformComponent>().position.y += 10;
		}
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryDown.getComponent<ColliderComponent>().collider)) {
		if (player.getComponent<TransformComponent>().position.y >= 600) {
			player.getComponent<TransformComponent>().position.y -= 10;
		}
		std::cout << "Boundary Hit!" << player.getComponent<TransformComponent>().position.y << std::endl;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, screenBoundaryRight.getComponent<ColliderComponent>().collider)) {
		if (player.getComponent<TransformComponent>().position.x >= 640) {
			player.getComponent<TransformComponent>().position.x-=10;
		}		
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, enemy.getComponent<ColliderComponent>().collider)) {
		//enemy.getComponent<TransformComponent>().position.x+=20;
		isRunning = false;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, enemy_toxic.getComponent<ColliderComponent>().collider)) {
		//enemy.getComponent<TransformComponent>().position.x+=20;
		isRunning = false;
	}
	else if (Collision::AABB(player.getComponent<ColliderComponent>().collider, enemy_fury.getComponent<ColliderComponent>().collider)) {
		//enemy.getComponent<TransformComponent>().position.x+=20;
		isRunning = false;
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
	SDL_RenderClear(renderer);
	tiles.clear();
	players.clear();
	enemies.clear();

	Mix_HaltMusic();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(groupMap);
}