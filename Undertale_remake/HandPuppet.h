#pragma once
#include "Obstacle.h"
#include "auxiliary.h"
class HandPuppet :
    public Obstacle
{
public:
    Vector2 pos;
	Vector2 dim;
	bool isDone;
	float alpha;

	HandPuppet();
	void Init() override;
	bool IsCollidedWithPlayer() override;
	float GetAreaOfCollision() override;
	void ApplyEffect() override;
	bool ShouldDespawn() override;
	void Update() override;
	void Display() override;
};

