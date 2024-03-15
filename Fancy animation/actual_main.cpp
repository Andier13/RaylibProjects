#include "actual_main.h"
#include "SecondOrderDynamics.h"
#include "raymath.h"

//SecondOrderDynamics animation(1, 0.5, 0);
//SecondOrderDynamics animation(2, 0, -2);
SecondOrderDynamics animation(3, 1, 0.5);
SecondOrderDynamics bounce(2, 0.2f, 2);
SecondOrderDynamics rotation(2, 1, 0.8);

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);
}

void update()
{
	
}

float angle;

void draw()
{
	ClearBackground(BLACK);
	Vector2 mouse = GetMousePosition();
	Vector2 pos = animation.Update(dt(), mouse);
	//std::cout << mouse.x << ' ' << mouse.y << ' ' << pos.x << ' ' << pos.y << std::endl;
	//DrawCircleV(pos, 30, RED);
	float MaxSpeed = 100000;
	float speed = mag(animation.GetDelta()) / dt();
	//std::cout << speed << std::endl;
	speed = clamp(speed, 0, MaxSpeed);
	//std::cout << speed << std::endl;
	float size = 100;
	float squishedSize = map(speed, 0, MaxSpeed, size, size*1.5f);
	//std::cout << squishedSize << std::endl;
	float bounceSize = bounce.Update(dt(), { squishedSize }).x;
	//std::cout << bounceSize << std::endl;
	Rectangle box = { pos.x, pos.y, bounceSize, size*size/bounceSize };
	//std::cout << animation.GetDelta().x << ' ' << animation.GetDelta().y << std::endl;
	angle = direction(animation.GetDelta());
	//std::cout << angle << std::endl;
	angle = rotation.UpdateCyclic(dt(), { angle }, {(float)TWO_PI}).x;
	//std::cout << angle << std::endl;
	DrawRectanglePro(box, { box.width / 2, box.height / 2 }, angle * RAD2DEG, DARKBLUE);
}

void trash()
{
	
}