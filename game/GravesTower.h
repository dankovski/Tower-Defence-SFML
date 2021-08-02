#pragma once
#include "Tower.h"
class GravesTower : public Tower
{
public:
	GravesTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	void attack();

};

