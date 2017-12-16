#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class AlienFury : public Component
{
public:
	TransformComponent *transform;

	int speed = 5;
	float scale = 1;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}
	void update(int pos_y);

private:

};