#include "StatBar.h"

StatBar::StatBar(Vector2 namePos, Rectangle healthBar, const char* fontFile) : 
	namePos(namePos), healthBar(healthBar), player(nullptr), font(LoadFont(fontFile))
{

}

StatBar::~StatBar()
{
	UnloadFont(font);
}

void StatBar::SetPlayer(Player* player)
{
	this->player = player;
}

void StatBar::Update()
{
}

void StatBar::Display()
{
	std::string text = player->GetName() + "   lv " + std::to_string(player->lvl);
	DrawTextEx(font, text.c_str(), namePos, healthBar.height, 0, WHITE);

	Vector2 temp = MeasureTextEx(font, "HP", healthBar.height, 0);
	DrawTextEx(font, "HP", {left(healthBar) - temp.x - healthBar.height, namePos.y}, healthBar.height, 0, WHITE);

	text = std::to_string(player->GetHP()) + "/" + std::to_string(player->GetMaxHP());
	DrawTextEx(font, text.c_str(), { right(healthBar) + healthBar.height, namePos.y }, healthBar.height, 0, WHITE);

	DrawRectangleRec(healthBar, RED);
	Rectangle actualHealth = healthBar;
	actualHealth.width = map((float)player->GetHP(), 0, (float)player->GetMaxHP(), 0, healthBar.width);
	DrawRectangleRec(actualHealth, YELLOW);
}
