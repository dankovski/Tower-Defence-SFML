#pragma once
#include "Tower.h"
class SlowTower :  public Tower
{

public:
	SlowTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition);
	void checkBulletsCollision(Enemy* mEnemyPointer);
	bool hasEnemyInRange(std::shared_ptr<Enemy> mEnemy);
	static int getInitValue();
	static int getInitRange();
	static int getInitDamage();
	static float getInitAttackSpeed();
	static float getInitSlowTime();
	static float getInitSlowPower();
	float getSlowTime();
	float getSlowPower();
	void upgrade();
private:
	float slowTime;
	float slowPower;
};

