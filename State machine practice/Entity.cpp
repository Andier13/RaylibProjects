#include "Entity.h"

void Entity::Update()
{
	stateManager.UpdateCurrentState();
}

void Entity::Display()
{
	DrawCircleV(position, 30, color);
}
