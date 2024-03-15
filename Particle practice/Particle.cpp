#include "Particle.h"

Particle::Particle() :
	pos({0}), vel({0}), acc({0}), 
	prevpos({0}), prevvel({0}), prevacc({0})
{
}

void Particle::ApplyForce(Vector2 force)
{
	acc = acc + force;
}

void Particle::Update()
{
	Vector2 jerk = acc - prevacc;
	prevpos = pos;
	prevvel = vel;
	prevacc = acc;
	
	pos = pos + vel * dt() + 0.5f * acc * dt() * dt() + 1.0f / 6 * jerk * dt() * dt(); // only dt^2 cuz jerk = dacc, not dacc/dt
	vel = vel + acc * dt() + 0.5f * jerk * dt(); //same here
	acc = { 0 };
}

void Particle::Display()
{
	Vector2 center = { WIDTH / 2, HEIGHT / 2 };
	float dist = mag(center - pos);
	ColorHSB col = {
		map(dist, 0, WIDTH / 2, 0, 255),
		clamp(map(pos.y, 0, HEIGHT, 255, 0), 0, 255),
		clamp((pos.y > HEIGHT * 0.75 ? map(pos.y, HEIGHT * 0.75, HEIGHT, 255, 0) : 255), 0, 255),
		255
	};
	DrawCircleV(pos, 21, BLACK);
	DrawCircleV(pos, 20, col);
	
}
