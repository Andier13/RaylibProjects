
#include "ObstacleType.h"
#include "PlayerType.h"

Color toColor(ObstacleType type)
{
	switch (type)
	{
	case ObstacleType::white: return WHITE;
		break;
	case ObstacleType::green: return GREEN;
		break;
	case ObstacleType::cyan: return SKYBLUE;
		break;
	case ObstacleType::orange: return ORANGE;
		break;
	default:
		return WHITE;
		break;
	}
}

Color toColor(PlayerType type)
{
	switch (type)
	{
	case PlayerType::red: return RED;
		break;
	case PlayerType::white: return WHITE;
		break;
	case PlayerType::blue: return BLUE;
		break;
	case PlayerType::cyan: return SKYBLUE;
		break;
	case PlayerType::orange: return ORANGE;
		break;
	case PlayerType::yellow: return YELLOW;
		break;
	default:
		return RED;
		break;
	}
}