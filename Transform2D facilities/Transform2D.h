#pragma once
#include "auxiliary.h"

class Transform2D
{
public:
	Vector2 origin = {};
	Vector2 position = {};
	Vector2 scale = {1, 1};
	float rotation = 0;

	Transform2D() = default;
	Vector2 GetGlobalPostion();
	float GetScaledRotation();
};

Transform2D operator*(Transform2D t1, Transform2D t2);
Vector2 operator*(Transform2D t, Vector2 v);
