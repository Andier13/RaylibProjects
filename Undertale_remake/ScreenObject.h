#pragma once

class ScreenObject
{
public:
	virtual void Update() = 0;
	virtual void Display() = 0;
	virtual ~ScreenObject() {};
};