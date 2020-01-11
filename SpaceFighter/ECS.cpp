#include "ECS.h"

void Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) {
	groupBitset[mGroup] = false;
	manager.removeFromGroup(mGroup);
}