#include "PlayerRed.h"

PlayerRed::PlayerRed() : Player("data/Sprites/Red heart.png")
{

}

void PlayerRed::Move()
{
	Vector2 left = { -1, 0 };
	Vector2 right = { 1, 0 };
	Vector2 up = { 0, -1 };
	Vector2 down = { 0, 1 };

	Vector2 dir = { 0, 0 };

	if (IsKeyDown('W'))
		dir = dir + up;
	if (IsKeyDown('A'))
		dir = dir + left;
	if (IsKeyDown('S'))
		dir = dir + down;
	if (IsKeyDown('D'))
		dir = dir + right;

	pos = pos + norm(dir) * speed * dt();
}

void PlayerRed::Update()
{
}
