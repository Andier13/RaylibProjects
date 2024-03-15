#include "PelletWhite.h"

PelletWhite::PelletWhite(Vector2 pos, float radius, float speed) :
	Obstacle(), pos(pos), radius(radius), vel({0, 0}), speed(speed),
	alreadyHit(false)
{
	
}

Circle PelletWhite::GetHitbox()
{
	return { pos, radius };
}

bool PelletWhite::IsCollidedWithPlayer()
{
	bool rez = CheckCollisionCircles(GetHitbox(), player->GetHitbox());
	//if (rez) alreadyHit = true;
	return rez;
}

float PelletWhite::GetAreaOfCollision()
{
	return PI/4 * area(GetCollisionRec(GetHitbox(), player->GetHitbox()));
}

void PelletWhite::Init()
{
	vel = norm(fromTo(pos, player->GetPos())) * speed;
}

void PelletWhite::ApplyEffect()
{
	if (type == ObstacleType::green)
		player->HealDamage(damageValue, alreadyHit, type);
	else
		player->TakeDamage(damageValue, alreadyHit, type);
}

void PelletWhite::Update()
{
	pos = pos + vel * dt();
}

bool PelletWhite::ShouldDespawn()
{
	const Rectangle screen = { 0, 0, WIDTH, HEIGHT };
	return !CheckCollisionRecs(GetHitbox(), screen) || alreadyHit;
}

void PelletWhite::Display()
{

	DrawCircleV(pos, radius+1, BLACK);
	DrawCircleV(pos, radius, toColor(type));
}
