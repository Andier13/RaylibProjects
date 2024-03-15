#include "TextButtton.h"

void TextButtton::Display()
{
	//auto [background, fill, outline] = (*resource)->blackAndWhite;
	Color background = parentScene->resource->blackAndWhite.bright;
	Color fill = parentScene->resource->blackAndWhite.darker;
	Color outline = parentScene->resource->blackAndWhite.darkest;
	float thickness = 0.1f * clickBox.height;
	DrawRectangleRec(clickBox, outline);
	Rectangle temp = rectFromCenter(center(clickBox), { clickBox.width - 2 * thickness, clickBox.height - 2 * thickness });
	DrawRectangleRec(temp, (CheckCollisionPointRec(GetMousePosition(), clickBox) ? fill : background));



	float fontSize = clickBox.height / 2 * textSize;
	float spacing = fontSize * 0.10f;
	Vector2 textDim = MeasureTextEx(font, text.c_str(), fontSize, spacing);
	Rectangle textBox = rectFromCenter(center(clickBox), textDim);
	DrawTextEx(parentScene->resource->defaultFont, text.c_str(), { textBox.x, textBox.y }, fontSize, spacing, outline);
}
