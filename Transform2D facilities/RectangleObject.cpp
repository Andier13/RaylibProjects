#include "RectangleObject.h"

void RectangleObject::Display()
{
	//DrawRectangleV(transform.GetGlobalPostion(), transform.scale * dim, WHITE);
	//DrawRectanglePro(RectangleFrom(LEFT, TOP, transform.GetGlobalPostion(), dim), { 0, 0 }, transform.rotation*RAD2DEG, WHITE);
	//DrawRectangleRec(RectangleFrom(CENTER, CENTER, transform.GetGlobalPostion(), dim*transform.scale), WHITE);
	//DrawRectanglePro(rect(transform.GetGlobalPostion(), dim * transform.scale), dim / 2 * transform.scale, transform.rotation*RAD2DEG, WHITE);
	//Vector2 dimproj = Rotate(Rotate(dim, transform.rotation) * transform.scale, -transform.GetScaledRotation());
	//dimproj = { abs(dimproj.x), abs(dimproj.y) };
	//DrawRectanglePro(rect(transform.GetGlobalPostion(), dimproj), dimproj / 2, transform.GetScaledRotation() *RAD2DEG, WHITE);
	
	
	Vector2 points[4] = {
		{dim.x / 2, dim.y / 2},
		{dim.x / 2, -dim.y / 2},
		{-dim.x / 2, -dim.y / 2},
		{-dim.x / 2, dim.y / 2},
	};

	for (auto& p : points)
		p = transform * p;

	for (int i = 0; i < 4; i++)
	{
		DrawLineV(points[i], points[(i + 1) % 4], MAGENTA);
	}

	Vector2 points2[4] = {
		{dim.x / 2, dim.y / 2},
		{dim.x / 2, -dim.y / 2},
		{-dim.x / 2, -dim.y / 2},
		{-dim.x / 2, dim.y / 2},
	};
	Vector2 offset = { 0, 200 };

	for (auto& p : points2)
		p = transform * p + offset;

	for (int i = 0; i < 4; i++)
	{
		DrawLineV(points2[i], points2[(i + 1) % 4], MAGENTA);
		DrawLineV(points[i], points2[i], MAGENTA);
	}
	
	/*
	constexpr int count = 12;
	Vector2 points[count] = {};
	for (int i = 0; i < count; i++)
	{
		points[i] = fromAngle(TWO_PI / count * i + TWO_PI/(2*count)) * mag(dim) *(i%2?0.5f:1.f);
		points[i] = transform * points[i];
		DrawLineExRound(transform.origin, points[i], 5, MAGENTA);
	}
	*/

	DrawLineExRound(transform.origin, transform.GetGlobalPostion(), 5, RED);
	
}
