#include "BattleScene1.h"
#include "HomingBulletsAttack.h"
#include "PauseAttack.h"
#include "BulletSpiralAttack.h"
#include "BulletSpiralHealAttack.h"
#include "ResizeBattlefieldAttack.h"
#include "BulletWallAttack.h"
#include "NewAttack1.h"
#include "BulletRainPathAttack.h"
#include "HandSwipesAttack.h"

BattleScene1::BattleScene1() : BattleScene()
{
	Rectangle boundary = rectFromCenter(WIDTH / 2, HEIGHT / 2 + 2 * HEIGHT / 10, WIDTH / 3, HEIGHT / 3);
	battlefield = new Battlefield(boundary);
	player = new PlayerRed();
	battlefield->SetPlayer(player);
	player->setBattlefield(battlefield);


	Vector2 namePos = { 50, bottom(battlefield->GetOuterBoundary()) + 30 };
	Rectangle healthBar = rectFromCenter(centerX(battlefield->GetOuterBoundary()), namePos.y, 100, 30);
	healthBar.y += healthBar.height / 2;
	statBar = new StatBar(namePos, healthBar, "data/Fonts/Battle.ttf");
	statBar->SetPlayer(player);

	Image bg = GenImageColor((int)WIDTH, (int)HEIGHT, BLACK);
	Image gradient = GenImageGradientV((int)WIDTH, (int)WIDTH / 2, BLANK, MAGENTA);
	Image mask = GenImageColor((int)WIDTH, (int)HEIGHT, WHITE);
	ImageDrawRectangleRec(&mask, battlefield->GetOuterBoundary(), BLANK);
	ImageDraw(&bg, gradient, { 0, 0, (float)gradient.width, (float)gradient.height },
		{ 0, (float)bg.height - gradient.height, (float)bg.width, (float)gradient.height }, WHITE);
	ImageDrawCircle(&bg, 50, 50, 10, YELLOW);
	ImageAlphaMask(&bg, mask);
	background = LoadTextureFromImage(bg);
	//UnloadImage(bg);
	//UnloadImage(gradient);
	//UnloadImage(mask);

	
	battleMusic = LoadMusicStream("data/Sounds/Enemy Approaching_cut.mp3");
	SetMusicVolume(battleMusic, 0.5);
	PlayMusicStream(battleMusic);



	//attackLoaders.push([]() ->Attack* {return new PauseAttack(3000); });
	//attackLoaders.push([]() ->Attack* {return new HandSwipesAttack(); });
	
	
	attackLoaders.push([]() ->Attack* {return new HomingBulletsAttack(5000); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(2000); });
	attackLoaders.push([]() ->Attack* {return new BulletSpiralAttack(10000); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(3000); });
	attackLoaders.push([]() ->Attack* {return new BulletSpiralHealAttack(10000); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(2000); });
	attackLoaders.push([]() ->Attack* {return new ResizeBattlefieldAttack(1000); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(1000); });
	attackLoaders.push([]() ->Attack* {return new BulletWallAttack(12000); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(2000); });
	attackLoaders.push([]() ->Attack* {return new BulletRainPathAttack(20); });
	attackLoaders.push([]() ->Attack* {return new PauseAttack(2000); });
	attackLoaders.push([]() ->Attack* {return new NewAttack1(30000); });
	
}

BattleScene1::~BattleScene1()
{
}