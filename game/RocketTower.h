#pragma once
#include "Tower.h"
#include "Bullet.h"


class RocketTower : public Tower{

private:
	std::vector<Bullet> bullets;
	sf::Texture* bulletTexture;

public:
	RocketTower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mAttackSpeed, sf::Texture* mBulletTexture);
	void attack();
	void render(double mDeltaTime);
	void checkBulletsCollision(Enemy* mEnemyPointer);
	void draw(sf::RenderWindow& mWindow);

};

