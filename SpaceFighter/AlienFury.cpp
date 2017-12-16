#include "AlienFury.h"

void AlienFury::update(int pos_y) {
	if (transform->position.x > -transform->width + 3) {
		transform->velocity.x = -1 * speed;
	}

	else
		transform->loop(pos_y);
}