#pragma once
#include "Tower.h"
#include <numbers>

class GravesTower : public Tower
{
public:
	GravesTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	void attack();
	static int getInitValue();
	static int getInitRange();
	static int getInitDamage();
	static float getInitAttackSpeed();
	void upgrade();

};

