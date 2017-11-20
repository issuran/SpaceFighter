#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class BackgroundComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect, destRect2;

	//The background scrolling offset
	int scrollingOffset = 0;

	bool animated = false;
	int frames = 0;
	//delay in miliseconds between frames 
	int speed = 100;

public:

	BackgroundComponent() = default;

	BackgroundComponent(const char* path) {
		setTex(path);
	}

	BackgroundComponent(const char* path, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	}

	~BackgroundComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		//get the position component
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;

		//Original size of the asset
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {

		if (scrollingOffset == 0) {
			destRect2.h = destRect.h;
			destRect2.y = destRect.y;

			destRect2.w = destRect.w;
			destRect2.x = destRect.w;
		}

		--scrollingOffset;

		if (scrollingOffset < -transform->width)
		{
			scrollingOffset = 0;
			destRect.x = srcRect.x;
			destRect2.x = srcRect.w;
		}

		destRect.x = srcRect.x + scrollingOffset;

		TextureManager::Draw(texture, srcRect, destRect);

		destRect2.x = destRect.x + transform->width;

		TextureManager::Draw(texture, srcRect, destRect2);
	}
};
