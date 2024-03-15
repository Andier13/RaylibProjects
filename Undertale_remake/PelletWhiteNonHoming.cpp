#include "PelletWhiteNonHoming.h"

PelletWhiteNonHoming::PelletWhiteNonHoming(Vector2 pos, float radius, float speed, Vector2 direction) :
	PelletWhite(pos, radius, speed), direction(direction)
{
	
}

void PelletWhiteNonHoming::Init()
{
	vel = direction * speed;
}
