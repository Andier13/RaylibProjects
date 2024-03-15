#pragma once

#include "auxiliary.h"
#include "ScreenObject.h"
#include "Obstacle.h"

class Player;

class Battlefield : public ScreenObject
{
	Rectangle boundary;
	float thickness;
	float rotation; //rotation from center, in degrees
	Player* player;
	std::vector<Obstacle*> obstacles;

public:

	Battlefield(Rectangle boundary);
	~Battlefield();
	void SetPlayer(Player* player);
	Player* GetPlayer();
	void AddObstacle(Obstacle* obstacle);
	void Resize(float w, float h);
	void Rotate(float angle);
	void SetRotation(float angle);
	float GetRotation();
	Rectangle GetBoundary();
	Rectangle GetOuterBoundary();
	void Update();
	void Display();
	void DisplayBackgroundObstacles();
	void DisplayForegroundObstacles();
};

