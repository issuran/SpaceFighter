#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class Alien : public Component
{
public:
	TransformComponent *transform;

	int speed = 3;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update();

private:

};