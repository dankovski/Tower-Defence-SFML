#pragma once
#include "Tower.h"
#include "Bullet.h"


class RocketTower : public Tower{

public:
	RocketTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	static int getInitValue();
	static int getInitRange();
	static int getInitDamage();
	static float getInitAttackSpeed();
};

