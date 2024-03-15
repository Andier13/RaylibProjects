#include "actual_main.h"
#include "Particle.h"
#include "Timer.h"

std::vector<Particle*> particles;
PeriodicTimer freq;

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);
	freq.Set(100);
}

void update()
{
	if (freq())
	{
		Particle* p = new Particle();
		p->pos = { WIDTH / 2, HEIGHT / 2 };
		float range = PI / 3;
		p->vel = fromAngle(-HALF_PI+random(-range/2, range/2)) * random(200, 500);
		particles.push_back(p);
	}
	for (auto p : particles)
	{
		//gravity
		p->ApplyForce({ 0, 200 });
		
		//side wind
		float dist = abs(p->pos.x - WIDTH * 0);
		float power = map(clamp(dist, 0, 200), 0, 200, 500, 0);
		p->ApplyForce({ power });
		dist = abs(p->pos.x - WIDTH);
		power = map(clamp(dist, 0, 200), 0, 200, 500, 0);
		p->ApplyForce({ -power });
		//circular wind
		/*Vector2 center = { WIDTH / 2, HEIGHT / 2 };
		Vector2 r = fromTo(center, p->pos);
		float dist = abs(mag(r) - 200);
		float power = (dist <= 100 ?
			map(clamp(dist, 0, 100), 0, 100, 5000, 0) :
			0);
		Vector2 force = fromAngle(direction(r) - HALF_PI - HALF_PI/2) * power;
		p->ApplyForce(force);*/
	}
	for (auto p : particles)
		p->Update();
	for (int i = particles.size() - 1; i >= 0; i--)
		if (particles[i]->pos.y-30>HEIGHT)
		{
			delete particles[i];
			for (int j = i + 1; j < particles.size(); j++)
				particles[j - 1] = particles[j];
			particles.pop_back();
		}
}

void draw()
{
	ClearBackground(BLACK);
	for (auto p : particles)
		p->Display();
}

void trash()
{
	for (auto p : particles)
		delete p;
}