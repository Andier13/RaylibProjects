#include "actual_main.h"
#include "Entity.h"
#include "EntityState.h"
#include "IdleState.h"
#include "ChaseState.h"

Entity enemy = {};

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);
	enemy.position = { WIDTH / 2, HEIGHT / 2 };
	enemy.stateManager.AddState("Idle", new IdleState(enemy));
	enemy.stateManager.AddState("Chase", new ChaseState(enemy));
}

void update()
{
	enemy.Update();
}

void draw()
{
	ClearBackground(BLACK);
	enemy.Display();
}

void trash()
{
	
}