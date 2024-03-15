#pragma once
#include "auxiliary.h"

class Particle
{
public:
	Vector2 pos;
	Vector2 vel;
	Vector2 acc;

	Vector2 prevpos;
	Vector2 prevvel;
	Vector2 prevacc;

	Particle();
	void ApplyForce(Vector2 force);
	void Update();
	virtual void Display();
	//To be impleneted:
	void ApplyImpulse(Vector2 impulse); //like applyforce but with velocity
	float mass = 1; //force and impulse should be divided by mass before being added
};

