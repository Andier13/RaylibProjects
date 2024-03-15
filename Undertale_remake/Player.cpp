#include "Player.h"

Player::Player(const char* textureFile, PlayerType type) : 
	battlefield(nullptr),
	/*heart(LoadTexture(textureFile)),*/ 
	hurt(LoadSound("data/Sounds/Taking Damage_cut.mp3")), 
	heal(LoadSound("data/Sounds/Restoring Health_cut.mp3")),
	speed(250), invincibilityDuration(1000), 
	lastTimeHit(timeSinceEpochMillisec() - invincibilityDuration),
	HP(20), maxHP(20), lvl(1), attack(0), defence(0), name("Frisk"),
	type(type), pos({0, 0}), prevPos({0, 0}), 
	collisionBoxRadius(16), hitboxRadius(14)
{
	Image temp = LoadImage(textureFile);
	int len = 2 * (int) collisionBoxRadius;
	ImageResizeNN(&temp, len, len);
	ImageColorTint(&temp, toColor(type));
	heart = LoadTextureFromImage(temp);
	UnloadImage(temp);
}

void Player::setBattlefield(Battlefield* battlefield)
{
	this->battlefield = battlefield;
	prevPos = pos = center(battlefield->GetBoundary());
}


void Player::PostUpdate()
{
	prevPos = pos;
}

void Player::CollideEdges()
{
	Rectangle boundary = battlefield->GetBoundary();
	Circle collisionBox = GetCollisionBox();
	if (left(collisionBox) < left(boundary))
		pos.x = left(boundary) + collisionBox.r;
	if (right(collisionBox) > right(boundary))
		pos.x = right(boundary) - collisionBox.r;
	if (top(collisionBox) < top(boundary))
		pos.y = top(boundary) + collisionBox.r;
	if (bottom(collisionBox) > bottom(boundary))
		pos.y = bottom(boundary) - collisionBox.r;
}

void Player::SetHP(int HPValue)
{
	HP = HPValue;
	if (HPValue < 0)
		HP = 0;
	if (HPValue > maxHP)
		HP = maxHP;
}

int Player::GetHP()
{
	return HP;
}

int Player::GetMaxHP()
{
	return maxHP;
}

std::string Player::GetName()
{
	return name;
}

Circle Player::GetHitbox() const
{
	return { pos, hitboxRadius };
}

Circle Player::GetCollisionBox() const
{
	return { pos, collisionBoxRadius };
}

Vector2 Player::GetPos() const
{
	return pos;
}

bool Player::IsInvincible()
{
	return (timeSinceEpochMillisec() - lastTimeHit < invincibilityDuration);
}

bool Player::IsMoving()
{
	return prevPos != pos;
}

void Player::TakeDamage(int damageValue, bool& succeded, ObstacleType obsType)
{
	succeded = false;
	bool movingCondition = true;
	switch (type)
	{
	//case PlayerType::red:
		//break;
	case PlayerType::white:
		if (obsType == ObstacleType::white)
		{
			HealDamage(damageValue, succeded, obsType);
			return;
		}
		break;
	//case PlayerType::blue:
		//break;
	case PlayerType::cyan:
		if (obsType == ObstacleType::white)
			movingCondition = IsMoving();
		if (obsType == ObstacleType::cyan)
			movingCondition = !IsMoving();
		break;
	case PlayerType::orange:
		if (obsType == ObstacleType::white)
			movingCondition = !IsMoving();
		if (obsType == ObstacleType::orange)
			movingCondition = IsMoving();
		break;
	//case PlayerType::yellow:
		//break;
	default:
		if (obsType == ObstacleType::cyan)
			movingCondition = IsMoving();
		if (obsType == ObstacleType::orange)
			movingCondition = !IsMoving();
		break;
	}
	
	/*if ((type == PlayerType::white && obsType == ObstacleType::white))
	{
		HealDamage(damageValue, obsType);
		return;
	}*/
	if (!movingCondition)
		return;
	succeded = true;
	if (IsInvincible())
		return;
	PlaySound(hurt);
	if (HP - damageValue < 0)
		HP = 0;
	else
		HP -= damageValue;
	lastTimeHit = timeSinceEpochMillisec();
}

void Player::HealDamage(int healValue, bool& succeded, ObstacleType obsType)
{
	if ((type == PlayerType::white && obsType == ObstacleType::green))
	{
		TakeDamage(healValue, succeded, obsType);
		return;
	}
	succeded = true;
	PlaySound(heal);
	if (HP + healValue > maxHP)
		HP = maxHP;
	else
		HP += healValue;
}

void Player::Display()
{
	//DrawTexturePro(heart, { 0, 0, (float)heart.width, (float)heart.height }, hitbox, {0, 0}, 0, WHITE);
	//NPatchInfo n = { { 0, 0, (float)heart.width, (float)heart.height } , 0, 0, 0, 0, NPATCH_NINE_PATCH};
	//DrawTextureNPatch(heart, n, hitbox, { 0, 0 }, 0, WHITE);
	uint64_t t = timeSinceEpochMillisec() - lastTimeHit;
	bool temp = (IsInvincible() && ((t%1000) / (1000 / 12))%2 == 0);
	Circle collisionBox = GetCollisionBox();
	DrawTexture(heart, (int)left(collisionBox), (int)top(collisionBox), (temp ? BLANK : toColor(type)));

	//Circle hitbox = GetHitbox();
	//DrawCircleLines(hitbox.x, hitbox.y, hitbox.r, GREEN);
	//DrawCircleLines(collisionBox.x, collisionBox.y, collisionBox.r, WHITE);
}

Player::~Player()
{
	UnloadTexture(heart);
	UnloadSound(hurt);
	UnloadSound(heal);
}
