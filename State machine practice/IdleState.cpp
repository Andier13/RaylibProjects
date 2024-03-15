#include "IdleState.h"

void IdleState::OnEnter()
{
	entity.color = GREEN;
}

void IdleState::Update()
{
	if (timeSinceEpochMillisec() - startTime > duration)
	{
		direction = RandomVector2();
		startTime = timeSinceEpochMillisec();
	}

	entity.position = entity.position + direction * speed * dt();

	if (mag(entity.position - GetMousePosition()) <= 300)
		manager->SwitchState("Chase");
}

IdleState::IdleState(Entity& entity) : EntityState(entity)
{
}
