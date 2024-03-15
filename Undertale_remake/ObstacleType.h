#pragma once

#include "auxiliary.h"

enum class ObstacleType
{
	white, green, cyan, orange
};

Color toColor(ObstacleType type);