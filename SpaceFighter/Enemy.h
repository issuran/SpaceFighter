#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class Enemy : public Component
{
public:
	TransformComponent *transform;

	int speed;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

private:

};