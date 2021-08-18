#pragma once
#include "Tower.h"



class StunTower : public Tower
{
public:
	StunTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	void checkBulletsCollision(Enemy* mEnemyPointer);
	bool hasEnemyInRange(std::shared_ptr<Enemy> mEnemy);
	static int getInitValue();
	static int getInitRange();
	static int getInitDamage();
	static float getInitAttackSpeed();
	static float getInitStunTime();
	float getStunTime();
	void upgrade();
private:
	float stunTime;
};

