#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class Enemy : public Component
{
public:
	TransformComponent *transform;

	int speed = 1;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		transform->velocity.x = -1 * speed;
	}

private:

};