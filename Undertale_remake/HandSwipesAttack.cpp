#include "HandSwipesAttack.h"

HandSwipesAttack::HandSwipesAttack() :
	Attack(30000), hand()
{
}

void HandSwipesAttack::Setup()
{
	Rectangle box = battlefield->GetBoundary();
	float dist = 100;
	float dim = box.height / 3;
	hand[0] = new HandPuppet();
	hand[1] = new HandPuppet();

	hand[0]->pos = { left(box) - dist - dim / 2, centerY(box)};
	hand[1]->pos = { right(box) + dist + dim / 2, centerY(box)};

	target[0] = hand[0]->pos;
	target[1] = hand[1]->pos;
	std::cout << target[0].x << ' ' << target[0].y << std::endl;
	std::cout << target[1].x << ' ' << target[1].y << std::endl;

	hand[0]->alpha = 0;
	hand[1]->alpha = 0;

	battlefield->AddObstacle(hand[0]);
	battlefield->AddObstacle(hand[1]);

	startTime = timeSinceEpochMillisec();
	sequence.Set({ 2000, 5000, 2000 });
}

void HandSwipesAttack::Update()
{
	if (sequence())
	{
		startTime = timeSinceEpochMillisec();
		switch (sequence.GetCounter())
		{
		case 1:
		{

		}
		break;
		case 2:
		{

		}
		break;
		case 3:
		{
			hand[0]->isDone = true;
			hand[1]->isDone = true;
		}
		break;
		default:
			break;
		}
	}

	switch (sequence.GetCounter())
	{
	case 0:
	{
		float alpha = clamp(map(timeSinceEpochMillisec() - startTime, 0, 2000, 0, 255), 0, 255);
		hand[0]->alpha = alpha;
		hand[1]->alpha = alpha;
	}
	break;
	case 1:
	{
		float t = clamp(map(timeSinceEpochMillisec() - startTime, 0, 500, 0, 1), 0, 1);
		Vector2 temp = lerp(target[0], target[1], t);
		//std::cout << t << ' ' << temp.x << ' ' << temp.y << std::endl;
		hand[0]->pos = swipe0.Update(dt(), lerp(target[0], target[1], t));
		hand[1]->pos = swipe1.Update(dt(), lerp(target[1], target[0], t));
		std::cout << hand[0]->pos.x << ' ' << hand[0]->pos.y << std::endl;
		std::cout << hand[1]->pos.x << ' ' << hand[1]->pos.y << std::endl;
	}
	break;
	case 2:
	{
		float alpha = clamp(map(timeSinceEpochMillisec() - startTime, 0, 2000, 255, 0), 0, 255);
		hand[0]->alpha = alpha;
		hand[1]->alpha = alpha;
	}
	break;
	default:
		break;
	}
	
}
