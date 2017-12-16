#include "AlienToxic.h"

void AlienToxic::update() {
	if (transform->position.x > -transform->width + 3) {
		transform->velocity.x = -1 * speed;
		if(transform->scale < 2)
			transform->scale += 0.05;
		else
			transform->scale = 1;
	}
		
	else
		transform->loop();
}