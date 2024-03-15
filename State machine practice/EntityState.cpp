#include "EntityState.h"

void EntityState::OnEnter()
{
}

void EntityState::OnExit()
{
}

void EntityState::Update()
{
	entity.position = entity.position + velocity * dt();
}

EntityState::EntityState(Entity& entity, const Vector2& velocity)
	: entity(entity), velocity(velocity)
{
}

EntityState::EntityState(Entity& entity)
	: entity(entity)
{
}