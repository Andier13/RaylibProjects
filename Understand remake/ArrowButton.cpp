#include "ArrowButton.h"

void ArrowButton::Display()
{
	Color background = parentScene->resource->currentColors.bright;
	Color outline = parentScene->resource->currentColors.darkest;
	Color fill = parentScene->resource->currentColors.darker;
	Rectangle box = clickBox;
	Vector2 center = ::center(box);
	float length = std::min(box.width, box.height);
	float radius = 0.50f * length / 2;
	float thickness = 0.05f * length;
	Rectangle outerBoundary = rectFromCenter(center, { box.width + thickness, box.height + thickness });
	Rectangle innerBoundary = rectFromCenter(center, { box.width - thickness, box.height - thickness });

	

	DrawRectangleRec(outerBoundary, outline);
	DrawRectangleRec(innerBoundary, (CheckCollisionPointRec(GetMousePosition(), clickBox) ? fill : background));

	if (star)
	{
		//Texture2D star_ = parentScene->resource->star;
		//Rectangle textureBoundary = rectFromCenter(center, { length * 0.75f * 1.1f * 1.3f, length * 0.75f * 1.3f });
		//DrawTexturePro(star_, { 0, 0, (float)star_.width, (float)star_.height }, textureBoundary, { 0, 0 }, 0, parentScene->resource->currentColors.darkest);
		//textureBoundary = rectFromCenter(center, { length * 0.75f * 1.1f, length * 0.75f });
		//DrawTexturePro(star_, { 0, 0, (float)star_.width, (float)star_.height }, textureBoundary, { 0, 0 }, 0, parentScene->resource->currentColors.bright);
		//
		/*
		radius = radius / sinf(PI *1.5/ 5);
		float trueAngle = 90 + 90;
		center = center + 1.f / 10 * radius * fromAngle(-PI / 2 - trueAngle * DEG2RAD);
		thickness = thickness / sinf(PI / 2 - PI *1.2f/ 5);
		DrawPoly(center, 5, radius + thickness, trueAngle, outline);
		DrawPoly(center, 5, radius, trueAngle, (active ? outline : background));
		*/
		radius = radius / sin(PI / 2 - PI / 5);
		center.y += 0.1f * radius;
		thickness = thickness / sin(PI / 2 - PI / 5);;
		DrawPoly(center, 5, radius + thickness, 180, outline);
		DrawPoly(center, 5, radius, 180, (active ? outline : background));
	}
	else
	{
		radius = radius / sinf(PI / 3);
		float trueAngle = angle + 90;
		center = center + 1.f / 3 * radius * fromAngle(-PI / 2 - trueAngle * DEG2RAD);
		thickness = thickness / sinf(PI / 2 - PI / 3);
		DrawPoly(center, 3, radius + thickness, trueAngle, outline);
		DrawPoly(center, 3, radius, trueAngle, (active ? outline : background));
	}

}
