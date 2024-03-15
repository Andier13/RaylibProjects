#include "HandPuppet.h"
#include "Player.h"

HandPuppet::HandPuppet() :
	pos({0}), dim{100, 100}, alpha(255)
{
	isDone = false;
}

void HandPuppet::Init()
{
}

bool HandPuppet::IsCollidedWithPlayer()
{
	return CheckCollisionRecs(rectFromCenter(pos, dim), player->GetHitbox());
}

float HandPuppet::GetAreaOfCollision()
{
	return 0.0f;
}

void HandPuppet::ApplyEffect()
{
	bool throwaway = false;
	player->TakeDamage(2, throwaway);
}

bool HandPuppet::ShouldDespawn()
{
	return isDone;
}

void HandPuppet::Update()
{
}

void HandPuppet::Display()
{
	DrawRectanglePro({ pos.x, pos.y, dim.x, dim.y }, dim / 2, 0, ColorAlpha(LIGHTGRAY, alpha/255));
}
