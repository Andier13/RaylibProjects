#pragma once
#include "ScreenObject.h"
#include "auxiliary.h"
class Player;
class Battlefield;

#include "ObstacleType.h"

class Obstacle : public ScreenObject
{
protected:
	Player* player;
	Battlefield* battlefield;
	ObstacleType type;
	int damageValue;
	bool isConstrainedWithinBoundary;
	int layer;

public:

	Obstacle(ObstacleType type = ObstacleType::white);
	void SetPlayer(Player* player);
	void SetBattlefield(Battlefield* battlefield);
	void SetType(ObstacleType type);
	void SetDamageValue(int damageValue);
	void SetToBackground(bool isInBackground = true);
	bool IsConstrainedWithinBoundary();
	void SetLayer(int layer);
	int GetLayer();
	virtual void Init() = 0;
	virtual bool IsCollidedWithPlayer() = 0;
	virtual float GetAreaOfCollision() = 0;
	virtual void ApplyEffect() = 0;
	virtual bool ShouldDespawn() = 0;
};