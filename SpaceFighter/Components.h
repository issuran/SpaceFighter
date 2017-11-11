#pragma once
#include "ECS.h"

class PositionComponent : public Component
{

private:
	int xpos;
	int ypos;

public:

	int x() { return xpos; }
	int y() { return ypos; }
	
	void init() override {
		xpos = 0;
		ypos = 0;
	}

	void update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};