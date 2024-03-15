#pragma once

#include "auxiliary.h"
#include "ScreenObject.h"
#include "Battlefield.h"
#include "PlayerType.h"
#include "ObstacleType.h"

class Player : ScreenObject
{
protected:
	Battlefield *battlefield;
	Vector2 pos;
	Vector2 prevPos;
	float collisionBoxRadius;
	float hitboxRadius;
	Texture2D heart;
	Sound hurt;
	Sound heal;
	uint64_t invincibilityDuration;
	uint64_t lastTimeHit;
	std::string name;
	PlayerType type;

public:
	int HP;
	int maxHP;
	int lvl;
	int attack;
	int defence;
	float speed;

public:

	Player(const char* textureFile, PlayerType type = PlayerType::red);
	//void init(const char* textureFile, Battlefield* battlefield);
	void setBattlefield(Battlefield* battlefield);
	virtual void Move() = 0;//controls only
	virtual void Update() = 0; //movement by external sources
	void PostUpdate(); //update prevPos
	void CollideEdges();
	void SetHP(int HPValue);
	int GetHP();
	int GetMaxHP();
	std::string GetName();
	Circle GetHitbox() const;
	Circle GetCollisionBox() const;
	Vector2 GetPos() const;
	bool IsInvincible();
	bool IsMoving();
	void TakeDamage(int damageValue, bool& succeded, ObstacleType obsType = ObstacleType::white);
	void HealDamage(int healValue, bool& succeded, ObstacleType obsType = ObstacleType::white);
	void Display();
	~Player();
};