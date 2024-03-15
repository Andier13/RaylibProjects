#pragma once
#include "Obstacle.h"
#include "Player.h"

class PelletWhite :
    public Obstacle
{
protected:
	Vector2 pos;
	Vector2 vel;
	float radius;
	float speed;
	bool alreadyHit;

public:

	PelletWhite(Vector2 pos, float radius, float speed);
	Circle GetHitbox();
	bool IsCollidedWithPlayer();
	float GetAreaOfCollision();
	virtual void Init();
	virtual void ApplyEffect();
	virtual void Update();
	virtual bool ShouldDespawn();
	virtual void Display();
};

