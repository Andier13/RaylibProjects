#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType type) : 
	player(nullptr), battlefield(nullptr), type(type), damageValue(0),
	isConstrainedWithinBoundary(false), layer(0)
{
}

void Obstacle::SetPlayer(Player* player)
{
	this->player = player;
}

void Obstacle::SetBattlefield(Battlefield* battlefield)
{
	this->battlefield = battlefield;
}

void Obstacle::SetType(ObstacleType type)
{
	this->type = type;
}

void Obstacle::SetDamageValue(int damageValue)
{
	this->damageValue = damageValue;
}

void Obstacle::SetToBackground(bool isInBackground)
{
	isConstrainedWithinBoundary = isInBackground;
}

bool Obstacle::IsConstrainedWithinBoundary()
{
	return isConstrainedWithinBoundary;
}

void Obstacle::SetLayer(int layer)
{
	this->layer = layer;
}

int Obstacle::GetLayer()
{
	return layer;
}
