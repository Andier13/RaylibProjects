#pragma once

#include "auxiliary.h"

enum class PlayerType
{
	red, white, blue, cyan, orange, yellow
};

Color toColor(PlayerType type);