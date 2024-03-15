#pragma once
#include "auxiliary.h"

enum class CellType
{
	Empty,
	Circle,
	Square,
	Triangle,
	Upside_down_triangle,
	Left_triangle,
	Right_triangle,
	Pentagon,
	Hexagon,
	Octogon
};

class Cell
{
public:
	Rectangle box = {};
	CellType type = CellType::Empty;
	bool active = false;

	void Display();
};

