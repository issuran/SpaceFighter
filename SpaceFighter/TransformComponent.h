#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{

public:

	Vector2D position;

	TransformComponent() {
		position.x = 0;
		position.y = 0;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void update() override {

	}
};