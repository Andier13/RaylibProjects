#include "BulletRainPathAttack.h"
#include "PelletWhiteNonHoming.h"

BulletRainPathAttack::BulletRainPathAttack(int count) :
	Attack(0), attackFreq(), interval(1200)
{
	duration = interval * count;
}

void BulletRainPathAttack::Setup()
{
	attackFreq.Set(interval);
	Rectangle b = battlefield->GetBoundary();
	size = 10.0f;
	count = b.width / (2 * size);
	gapCount = 5;
	gapStart = (count-gapCount)/2;
	maxDeviation = 8;
}

void BulletRainPathAttack::Update()
{
	Rectangle b = battlefield->GetBoundary();
	Vector2 source = { left(b) + size, top(b) - 40 };
	if (attackFreq())
	{
		ObstacleType gapType = (probability(0.5) ? ObstacleType::cyan : ObstacleType::orange);
		for (int i = 0; i < count; i++)
		{
			Vector2 offset = {0, random(-size, size) * 0.75};
			Obstacle* pellet = new PelletWhiteNonHoming(source + offset, size-2, 150, { 0, 1 });
			if (gapStart <= i && i < gapStart + gapCount)
				pellet->SetType(gapType);
			pellet->SetDamageValue(3);
			pellet->SetToBackground();
			battlefield->AddObstacle(pellet);
			source.x += 2 * size;
		}
		gapStart = floor(random(
			std::max(gapStart - maxDeviation, 0), 
			std::min(gapStart + maxDeviation, count - gapCount) + 1
		));
	}
}
