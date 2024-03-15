#pragma once

#include "Transform2D.h"

class RectangleObject
{
public:
	Transform2D transform;
	Vector2 dim = { 50, 50 };

	void Display();
};


