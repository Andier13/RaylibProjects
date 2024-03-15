#include "Battlefield.h"
#include "Player.h"

void Battlefield::Resize(float newWidth, float newHeight)
{
	boundary = rectFromCenter(centerX(boundary), centerY(boundary), newWidth, newHeight);
}

void Battlefield::Rotate(float angle)
{
	rotation += angle;
}

void Battlefield::SetRotation(float angle)
{
	rotation = angle;
}

float Battlefield::GetRotation()
{
	return rotation;
}

Rectangle Battlefield::GetBoundary()
{
	return boundary;
}

Rectangle Battlefield::GetOuterBoundary()
{
	return { boundary.x - thickness, boundary.y - thickness, boundary.width + 2 * thickness, boundary.height + 2 * thickness };
}

void Battlefield::Update()
{
	
	
	if (player != nullptr)
	{
		player->Update();
		player->Move();
		player->CollideEdges();
	}

	for (auto obs : obstacles)
		obs->Update();

	for (auto obs : obstacles)
		if (obs->IsCollidedWithPlayer())
			obs->ApplyEffect();

	//DeleteAll(obstacles, [](Obstacle* obs)->bool {return obs->ShouldDespawn();});

	for (int i = (int)obstacles.size() - 1; i >= 0; i--)
		if (obstacles[i]->ShouldDespawn())
		{
			delete obstacles[i];
			for (int j = i + 1; j < obstacles.size(); j++)
				obstacles[j - 1] = obstacles[j];
			obstacles.pop_back();
		}
	
	if (player != nullptr)
		player->PostUpdate();
	
}

Battlefield::Battlefield(Rectangle boundary) : 
	boundary(boundary), thickness(10), rotation(0), player(nullptr)
{
	
}

Battlefield::~Battlefield()
{
	for (auto obs : obstacles)
		delete obs;
}

void Battlefield::SetPlayer(Player* player)
{
	this->player = player;
}

Player* Battlefield::GetPlayer()
{
	return player;
}

void Battlefield::AddObstacle(Obstacle* obstacle)
{
	obstacles.push_back(obstacle);
	obstacle->SetPlayer(player);
	obstacle->SetBattlefield(this);
	obstacle->Init();
}

void Battlefield::Display()
{
	DrawRectangleLinesEx(GetOuterBoundary(), thickness, WHITE);
	/*Rectangle b = GetOuterBoundary();
	b.x = centerX(b);
	b.y = centerY(b);
	Vector2 origin = { b.width / 2, b.height / 2 };
	DrawRectanglePro(b, origin, rotation, { 0, 255, 0, 127 });*/
}

void Battlefield::DisplayBackgroundObstacles()
{
	std::vector<Obstacle*> v;
	for (auto obs : obstacles)
		if (obs->IsConstrainedWithinBoundary())
			v.push_back(obs);
	if (v.size() == 0)
		return;
	for (int i = 0; i < v.size() - 1; i++)
		for (int j = i + 1; j < v.size(); j++)
			if (!(v[i]->GetLayer() <= v[j]->GetLayer()))
				std::swap(v[i], v[j]);
	for (auto obs : v)
		obs->Display();
}

void Battlefield::DisplayForegroundObstacles()
{
	std::vector<Obstacle*> v;
	for (auto obs : obstacles)
		if (!obs->IsConstrainedWithinBoundary())
			v.push_back(obs);
	if (v.size() == 0)
		return;
	for (int i = 0; i < v.size() - 1; i++)
		for (int j = i + 1; j < v.size(); j++)
			if (!(v[i]->GetLayer() <= v[j]->GetLayer()))
				std::swap(v[i], v[j]);
	for (auto obs : v)
		obs->Display();
}
