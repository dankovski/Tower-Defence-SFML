#pragma once
#include "Tower.h"
#include "Bullet.h"


class RocketTower : public Tower{


public:
	RocketTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);

};

