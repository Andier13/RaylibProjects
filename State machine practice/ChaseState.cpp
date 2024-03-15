#include "ChaseState.h"

void ChaseState::OnEnter()
{
	entity.color = RED;
}

void ChaseState::Update()
{
	Vector2 mouse = GetMousePosition();
	Vector2 dist = fromTo(entity.position, mouse);
	direction = norm(dist);

	if (mag(dist) >= 100)
		entity.position = entity.position + direction * speed * dt();

	
	if (mag(dist) >= 600)
		manager->SwitchState("Idle");
}

ChaseState::ChaseState(Entity& entity) : 
	EntityState(entity)
{
}
