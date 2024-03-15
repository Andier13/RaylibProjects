#include "BulletWallAttack.h"
#include "PelletWhiteNonHoming.h"

BulletWallAttack::BulletWallAttack(uint64_t duration) : 
	Attack(duration), attackFreq(), colorFlag()
{
}

void BulletWallAttack::Setup()
{
	attackFreq.Set(2000);
	colorFlag = false;
}

void BulletWallAttack::Update()
{
	Rectangle b = battlefield->GetBoundary();
	float size = 10.0f;
	int count = b.height / (2 * size);
	Vector2 source = { left(b) - 40, top(b) + size };
	if (attackFreq())
	{
		for (int i = 0; i < count; i++)
		{
			Obstacle* pellet = new PelletWhiteNonHoming(source, 8.0f, 200, { 1, 0 });
			pellet->SetType((colorFlag ? ObstacleType::cyan : ObstacleType::orange));
			pellet->SetDamageValue(3);
			pellet->SetToBackground();
			battlefield->AddObstacle(pellet);
			source.y += 2 * size;
		}
		colorFlag = !colorFlag;
	}
}
