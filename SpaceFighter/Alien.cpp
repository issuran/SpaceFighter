#include "Alien.h"

void Alien::update() {
	if (transform->position.x > -transform->width + 3)
		transform->velocity.x = -1 * speed;
	else
		transform->loop();	
}