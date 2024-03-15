#include "PelletWhiteBouncing.h"

PelletWhiteBouncing::PelletWhiteBouncing(Vector2 pos, float radius, float speed, Vector2 direction, uint64_t lifespan) :
	PelletWhiteNonHoming(pos, radius, speed, direction), lifespan(lifespan)
{
}

void PelletWhiteBouncing::Init()
{
	PelletWhiteNonHoming::Init();
	lifetime.Set(lifespan);
}

void PelletWhiteBouncing::Update()
{
	PelletWhiteNonHoming::Update();
	if (shouldExit)
		return;
	Rectangle boundary = battlefield->GetBoundary();
	Circle collisionBox = GetHitbox();
	if (left(collisionBox) < left(boundary))
		pos.x = 2 * (left(boundary) + radius) - pos.x;
	if (right(collisionBox) > right(boundary))
		pos.x = 2 * (right(boundary) - radius) - pos.x;
	if (top(collisionBox) < top(boundary))
		pos.y = 2 * (top(boundary) + radius) - pos.y;
	if (bottom(collisionBox) > bottom(boundary))
		pos.y = 2 * (bottom(boundary) - radius) - pos.y;

	if (left(collisionBox) < left(boundary) ||
		right(collisionBox) > right(boundary))
		vel.x = -vel.x;
	if (top(collisionBox) < top(boundary) ||
		bottom(collisionBox) > bottom(boundary))
		vel.y = -vel.y;

	if (lifetime())
		shouldExit = true;
}
