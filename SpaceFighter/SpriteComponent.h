#pragma once

#include"Components.h"
#include"SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
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
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;

		//Original size of the asset
		srcRect.w = 106;
		srcRect.h = 36;

		//Image asset scaled eg x2
		/*destRect.w = 212;
		destRect.h = 72;*/
		destRect.w = 106;
		destRect.h = 36;
	}

	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};
