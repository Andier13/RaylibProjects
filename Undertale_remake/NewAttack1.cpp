#include "NewAttack1.h"
#include "PelletWhiteBouncing.h"

NewAttack1::NewAttack1(uint64_t duration) :
	Attack(duration), first()
{
}

void NewAttack1::Setup()
{
	attackFreq.Set(2000);
	first = true;
}

void NewAttack1::Update()
{
	if (attackFreq() || first)
	{
		first = false;
		Vector2 source = center(battlefield->GetBoundary());
		Obstacle* pellet = new PelletWhiteBouncing(source, 8.0f, 200, fromAngle(random(TWO_PI)), 30000);
		pellet->SetDamageValue(4);
		if (probability_percent(50))
			pellet->SetType(ObstacleType::green);
		battlefield->AddObstacle(pellet);
	}
}
