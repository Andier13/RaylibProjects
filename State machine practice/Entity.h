#pragma once
#include "auxiliary.h"
#include "StateManager.h"

class Entity
{
public:
	Vector2 position = { 0, 0 };
	StateManager stateManager = {};
	Color color = BLUE;
	
	void Update();
	void Display();

	Entity() = default;
};

