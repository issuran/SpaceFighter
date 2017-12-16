#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class AlienToxic : public Component
{
public:
	TransformComponent *transform;

	int speed = 2;
	float scale = 1;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}
	void update();

private:

};