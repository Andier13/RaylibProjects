#include "BattleScene.h"

BattleScene::BattleScene() :
	battlefield(nullptr), player(nullptr), statBar(nullptr), 
	background(), enemy(), battleMusic(),
	attackTimer(), attackLoaders(), currentAttack(nullptr)
{
}

void BattleScene::Update()
{
	//UpdateOther();

	if (currentAttack != nullptr)
		currentAttack->Update();
	
	if (currentAttack == nullptr || attackTimer())
	{
		if (currentAttack != nullptr)
		{
			delete currentAttack;
			currentAttack = nullptr;
		}
		if (!attackLoaders.empty())
		{
			currentAttack = attackLoaders.front()();
			attackLoaders.pop();
			currentAttack->SetPlayer(player);
			currentAttack->SetBattlefield(battlefield);
			currentAttack->Setup();
			attackTimer.Set(currentAttack->GetDuration());
		}
	}

	battlefield->Update();
	statBar->Update();
	if (IsMusicReady(battleMusic))
		UpdateMusicStream(battleMusic);
}

void BattleScene::Draw()
{
	ClearBackground(BLACK);
	DrawRectangleRec(battlefield->GetBoundary(), BLACK);
	battlefield->DisplayBackgroundObstacles();
	battlefield->Display();

	BeginTextureMode(test);//uses mathematical coords to draw

	//GetBackgroundTexture
	ClearBackground(BLACK);
	float t = abs(sin(0.5 * GetTime() * PI));
	float temp_height = lerp(HEIGHT / 4, HEIGHT*3/4, t);
	DrawRectangleGradientV(0, 0, WIDTH, temp_height, { 0, 204, 255 , 255}, BLACK);

	////DrawTextureV(background, { 0, 0 }, WHITE);
	//Rectangle screen = { 0, 0, WIDTH, HEIGHT };
	//screen = computerCoordsToMathCoords(screen);
	//Rectangle dest = { WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT };
	////dest = computerCoordsToMathCoords(dest);
	//Vector2 origin = { dest.width/2, dest.height/2 };
	//// dest(x, y) = center of rotation
	//// origin = offset from corner of rectangle, NOT screen
	//DrawCircle(dest.x - origin.x, dest.y - origin.y, 10, WHITE);
	//DrawCircle(dest.x, dest.y, 10, WHITE);
	//DrawRectanglePro(dest, origin, 30 * GetTime(), {127, 127, 0, 127});
	//DrawTexturePro(background, screen, dest, origin, 180, WHITE);

	Rectangle crop = computerCoordsToMathCoords(battlefield->GetOuterBoundary());
	crop.x = centerX(crop);
	crop.y = centerY(crop);
	Vector2 cropOrigin = { crop.width / 2, crop.height / 2 };
	float rotation = -battlefield->GetRotation();
	BeginBlendMode(BLEND_SUBTRACT_COLORS);
	DrawRectanglePro(crop, cropOrigin, rotation, BLANK); //aka drawn from center
	EndBlendMode();
	EndTextureMode();
	DrawTextureV(test.texture, { 0, 0 }, WHITE);


	//DrawTextureV(background, { 0, 0 }, WHITE);
	/*float t = abs(sin(0.5 * GetTime() * PI));
	float temp_height = lerp(HEIGHT/2, HEIGHT, t);
	Rectangle temp_rect = { 0, 0, WIDTH, temp_height };
	DrawRectangleGradientV(temp_rect.x, HEIGHT-temp_rect.height, temp_rect.width, temp_rect.height, BLANK, {255, 0, 0, 127});
	*/

	statBar->Display();

	battlefield->DisplayForegroundObstacles();
	player->Display();

	DrawFPS(0, 0);
}

BattleScene::~BattleScene()
{
	delete battlefield;
	delete player;
	delete statBar;
	UnloadTexture(background);
	//UnloadTexture(enemy);
	UnloadMusicStream(battleMusic);
	UnloadRenderTexture(test);
}
