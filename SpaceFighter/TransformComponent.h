#pragma once
#include "Components.h"
#include "Vector2D.h"
#include <ctime>

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 36;
	int width = 106;
	float scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float sc) {
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.Zero();
	}

	TransformComponent(float x, float y, int h, int w, float sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
		srand(time(0));
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	void loop() {
		position.x = 800;
		position.y = random_position_y();
	}

	void loop(float pos_y) {
		position.x = 800;
		position.y = pos_y;
	}

	float random_position_y() {

		return rand() % 500 + 1;
	}
};