#include "BulletSpiralHealAttack.h"
#include "PelletWhiteNonHoming.h"

BulletSpiralHealAttack::BulletSpiralHealAttack(uint64_t duration) :
	Attack(duration), spiral(duration), healFreq()
{
}

void BulletSpiralHealAttack::Setup()
{
	spiral.SetPlayer(player);
	spiral.SetBattlefield(battlefield);
	spiral.Setup();
	Rectangle boundary = battlefield->GetOuterBoundary();
	Vector2 source = { left(boundary) - 50, top(boundary) - 200 };
	source.x = (WIDTH / 2 - source.x) + WIDTH / 2;
	spiral.SetSource(source);
	healFreq.Set(3000);
}

void BulletSpiralHealAttack::Update()
{
	spiral.Update();
	float size = 8.0f;
	Rectangle boundary = battlefield->GetBoundary();
	Vector2 source = { random(left(boundary) + size, right(boundary) - size), top(boundary) - 20 };
	if (healFreq())
	{
		Obstacle* pellet = new PelletWhiteNonHoming(source, 8.0f, 80, { 0, 1 });
		pellet->SetType(ObstacleType::green);
		pellet->SetDamageValue(3);
		pellet->SetToBackground();
		battlefield->AddObstacle(pellet);
	}
}
