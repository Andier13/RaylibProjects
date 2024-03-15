#pragma once
#include "auxiliary.h"
#include "ResourceClass.h"
#include "Scene.h"

class Button
{
public:
	Rectangle clickBox{};
	Scene* parentScene = nullptr;

	bool IsPressed();
	virtual void Display() = 0;
};

