#include "HomingBulletsAttack.h"
#include "PelletWhite.h"

HomingBulletsAttack::HomingBulletsAttack(uint64_t duration) :
	Attack(duration), attackFreq()
{

}

void HomingBulletsAttack::Setup()
{
	attackFreq.Set(800);
}

void HomingBulletsAttack::Update()
{
	Vector2 playerPos = player->GetPos();
	Vector2 attackPos = fromAngle(random(TWO_PI)) * random(100, 200) + playerPos;
	if (attackFreq())
	{
		if (probability(0.8f))
		{
			Obstacle* pellet = new PelletWhite(attackPos, 8.0f, 100);
			pellet->SetDamageValue(3);
			pellet->SetToBackground();
			battlefield->AddObstacle(pellet);
		}
		else
		{
			Obstacle* pellet = new PelletWhite(attackPos, 8.0f, 80);
			pellet->SetType(ObstacleType::green);
			pellet->SetDamageValue(2);
			pellet->SetToBackground();
			battlefield->AddObstacle(pellet);
		}
	}
}
