#pragma once

#include "auxiliary.h"

class SecondOrderDynamics
{

	Vector2 xp; // previous input
	Vector2 y, yd; // state variables
	float k1, k2, k3; // dynamics constants
	bool first;
public:
	/*
	* f = natural frequency (speed of response, frequency after response)
	* z = damping coefficient (0 - undamped, 0<1 - regular damping, >=1 - won't vibrate
	* the bigger it is the slower it will respond)
	* r = initial response (how fast it accelerates from where it was)
	* (0 - freefall, 0<1 - jolt, >1 - overshoot, <0 anticipation)
	*/
	SecondOrderDynamics(float f, float z, float r);
	/*
	* t = dt()
	* x = the path to follow
	*/
	Vector2 Update(float T, Vector2 x/*, Vector2 xd = null*/);
	Vector2 UpdateCyclic(float T, Vector2 x, Vector2 mod);
	Vector2 GetDelta();
};