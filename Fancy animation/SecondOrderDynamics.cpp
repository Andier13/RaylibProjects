#include "SecondOrderDynamics.h"
#include "auxiliary.h"

SecondOrderDynamics::SecondOrderDynamics(float f, float z, float r)
{
	// compute constants
	k1 = z / (PI * f);
	k2 = 1 / ((2 * PI * f) * (2 * PI * f));
	k3 = r * z / (2 * PI * f);
	// initialize variables
	first = true;
	//xp = x0;
	//y = x0;
	xp = { 0, 0 };
	y = { 0, 0 };
	yd = { 0, 0 };
}

Vector2 SecondOrderDynamics::Update(float T, Vector2 x/*, Vector2 xd = null*/)
{
	//if (xd == null) { // estimate velocity
	//	xd = (x - xp) / T;
	//	xp = x;
	//}
	if (first)
	{
		first = false;
		xp = x;
		y = x;
	}
	if (T == 0)
		return x;
	Vector2 xd = (x - xp) / T;
	xp = x;
	float k2_stable = std::max(k2, 1.1f * (T * T / 4 + T * k1 / 2)); // clamp k2 to guarantee stability 
	y = y + T * yd; // integrate position by velocity
	yd = yd + T * (x + k3 * xd - y - k1 * yd) / k2_stable; // integrate velocity by acceleration
	return y;
}

Vector2 SecondOrderDynamics::UpdateCyclic(float T, Vector2 x, Vector2 mod)
{
	//if (xd == null) { // estimate velocity
	//	xd = (x - xp) / T;
	//	xp = x;
	//}
	if (first)
	{
		first = false;
		xp = x;
		y = x;
	}
	x.x = closestModValue(y.x, x.x, mod.x);
	//x.y = closestModValue(y.y, x.y, mod.y);

	if (T == 0)
		return x;
	Vector2 xd = (x - xp) / T;
	xp = x;
	float k2_stable = std::max(k2, 1.1f * (T * T / 4 + T * k1 / 2)); // clamp k2 to guarantee stability 
	y = y + T * yd; // integrate position by velocity
	yd = yd + T * (x + k3 * xd - y - k1 * yd) / k2_stable; // integrate velocity by acceleration
	return y;
}

Vector2 SecondOrderDynamics::GetDelta()
{
	return yd;
}

void SecondOrderDynamics::Reset()
{
	first = true;
}
