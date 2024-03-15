#include "actual_main.h"
#include "RectangleObject.h"

RectangleObject box1, box2;
std::vector<Vector2> points{};

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);
	SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
	box1.transform.scale = { 2, 1 };
	box1.transform.origin = { WIDTH / 2, HEIGHT / 2 };
	box1.transform.position = { 200, 0 };
	//box2.transform.position = { 100, 100 };
	
}

void update()
{
	//box1.transform.position.x += 50 * dt();
	box1.transform.rotation += PI/5 * dt();
	Transform2D box1to2transform = {};
	//box1to2transform.scale = { 1.5f+sinf(2*PI/5*GetTime()), 1};
	box1to2transform.scale = { 1.5f,  norm(box1.transform.GetGlobalPostion()-box1.transform.origin).y };
	box1to2transform.rotation = PI / 4 * (float)GetTime();
	box1to2transform.position = { 100, 0 };
	box2.transform = box1to2transform * box1.transform;
	points.push_back(box2.transform.GetGlobalPostion());
	//points.push_back(box1.transform.GetGlobalPostion());
}

void draw()
{
	ClearBackground({ 52, 52, 52, 100 });

	box1.Display();
	box2.Display();

	DrawLineStrip(points.data(), (int)points.size(), DARKBLUE);

	/*
	Rectangle box[9] = {};
	Vector2 dim = { 250, 150 };

	box[0] = RectangleFrom(LEFT, TOP, { 0, 0 }, dim);
	box[1] = RectangleFrom(CENTER, TOP, { WIDTH / 2, 0 }, dim);
	box[2] = RectangleFrom(RIGHT, TOP, { WIDTH, 0 }, dim);
	box[3] = RectangleFrom(LEFT, CENTER, { 0, HEIGHT / 2 }, dim);
	box[4] = RectangleFrom(CENTER, CENTER, { WIDTH / 2, HEIGHT / 2 }, dim);
	box[5] = RectangleFrom(RIGHT, CENTER, { WIDTH, HEIGHT / 2 }, dim);
	box[6] = RectangleFrom(LEFT, BOTTOM, { 0, HEIGHT }, dim);
	box[7] = RectangleFrom(CENTER, BOTTOM, { WIDTH / 2, HEIGHT }, dim);
	box[8] = RectangleFrom(RIGHT, BOTTOM, { WIDTH, HEIGHT }, dim);

	for (const auto& b : box)
	{
		DrawRectangleRec(b, WHITE);
	}
	Font font = GetFontDefault();
	const char* text = "Flower\nwar";
	float fontSize = 20;
	float spacing = fontSize * 0.1f;

	
	DrawTextFrom(font, text, LEFT, TOP, { 0, 0 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, TOP, { WIDTH / 2, 0 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, TOP, { WIDTH, 0 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, LEFT, CENTER, { 0, HEIGHT / 2 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, CENTER, { WIDTH / 2, HEIGHT / 2 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, CENTER, { WIDTH, HEIGHT / 2 }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, LEFT, BOTTOM, { 0, HEIGHT }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, BOTTOM, { WIDTH / 2, HEIGHT }, fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, BOTTOM, { WIDTH, HEIGHT }, fontSize, spacing, BLACK);
	

	DrawTextFrom(font, text, LEFT, TOP, GetRectangleAlignmentPoint(box[8], LEFT, TOP), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, TOP, GetRectangleAlignmentPoint(box[7], CENTER, TOP), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, TOP, GetRectangleAlignmentPoint(box[6], RIGHT, TOP), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, LEFT, CENTER, GetRectangleAlignmentPoint(box[5], LEFT, CENTER), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, CENTER, GetRectangleAlignmentPoint(box[4], CENTER, CENTER), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, CENTER, GetRectangleAlignmentPoint(box[3], RIGHT, CENTER), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, LEFT, BOTTOM, GetRectangleAlignmentPoint(box[2], LEFT, BOTTOM), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, CENTER, BOTTOM, GetRectangleAlignmentPoint(box[1], CENTER, BOTTOM), fontSize, spacing, BLACK);
	DrawTextFrom(font, text, RIGHT, BOTTOM, GetRectangleAlignmentPoint(box[0], RIGHT, BOTTOM), fontSize, spacing, BLACK);
	*/
}

void trash()
{
	
}