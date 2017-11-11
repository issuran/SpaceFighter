#pragma once

#include"Components.h"
#include"SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent *position;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		//get the position component
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;

		//Original size of the asset
		srcRect.w = 106;
		srcRect.h = 36;

		//Image asset scaled
		destRect.w = 212;
		destRect.h = 72;
	}

	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};
