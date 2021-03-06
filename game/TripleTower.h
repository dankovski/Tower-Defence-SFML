#pragma once
#include "Tower.h"
class TripleTower : public Tower
{
public:
	TripleTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	void attack();
	static int getInitValue();
	static int getInitRange();
	static int getInitDamage();
	static float getInitAttackSpeed();
};

