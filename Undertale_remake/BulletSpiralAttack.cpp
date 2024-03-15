#include "BulletSpiralAttack.h"
#include "PelletWhiteNonHoming.h"

BulletSpiralAttack::BulletSpiralAttack(uint64_t duration) :
	Attack(duration), count(12), phase(0), deltaPhase(TWO_PI / (19)),
	source({ WIDTH / 2, HEIGHT / 2 })
{
}

void BulletSpiralAttack::SetSource(Vector2 source)
{
	this->source = source;
}

void BulletSpiralAttack::Setup()
{
	attackFreq.Set(500);
	Rectangle boundary = battlefield->GetOuterBoundary();
	source = { left(boundary) - 50, top(boundary) - 200 };
}

void BulletSpiralAttack::Update()
{

	if (attackFreq())
	{
		for (int i = 0; i < count; i++)
		{
			float angle = map((float)i, 0, (float)count, 0, TWO_PI) + phase;

			Obstacle* pellet = new PelletWhiteNonHoming(source, 8.0f, 100, fromAngle(angle));
			pellet->SetDamageValue(4);
			battlefield->AddObstacle(pellet);

		}
		phase += deltaPhase;
	}
}
