#include "SlowTower.h"



SlowTower::SlowTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
	slowTime = getInitSlowTime();
	slowPower = getInitSlowPower();
};

void SlowTower::checkBulletsCollision(Enemy* mEnemyPointer)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isColliding(mEnemyPointer->getGlobalBounds())) {
			bullets.erase(bullets.begin() + i);
			mEnemyPointer->receiveDamage(damage);
			mEnemyPointer->startSlow(slowTime, slowPower);
			i--;
		}

	}

}

bool SlowTower::hasEnemyInRange(std::shared_ptr<Enemy> mEnemy) {

	if (mEnemy->isStunned() || mEnemy->isSlowed()) {
		return false;
	}

	sf::FloatRect mEnemyGlobalBounds = mEnemy->getGlobalBounds();
	float xDistance = abs(range.getPosition().x - (mEnemyGlobalBounds.left + mEnemyGlobalBounds.width / 2.0));
	float yDistance = abs(range.getPosition().y - (mEnemyGlobalBounds.top + mEnemyGlobalBounds.height / 2.0));

	if (xDistance > (mEnemyGlobalBounds.width / 2.0 + range.getRadius())) { return false; }
	if (yDistance > (mEnemyGlobalBounds.height / 2.0 + range.getRadius())) { return false; }

	if (xDistance <= (mEnemyGlobalBounds.width / 2.0)) { return true; }
	if (yDistance <= (mEnemyGlobalBounds.height / 2.0)) { return true; }

	return (sqrt(pow((xDistance - mEnemyGlobalBounds.width / 2.0), 2.0) + pow((yDistance - mEnemyGlobalBounds.height / 2.0), 2)) <= range.getRadius());
}

void SlowTower::upgrade()
{
	level++;
	range.setRadius(range.getRadius() + 10);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	attackSpeed += 0.05;
	value += getUpgradeCost();
	slowTime += 0.05;
	slowPower -= 0.02;
}



int SlowTower::getInitValue()
{
	return 120;
}

int SlowTower::getInitRange()
{
	return 200;
}

int SlowTower::getInitDamage()
{
	return 0;
}

float SlowTower::getInitAttackSpeed()
{
	return 1.0;
}

float SlowTower::getInitSlowTime()
{
	return 0.5;
}

float SlowTower::getInitSlowPower()
{
	return 0.4;
}

float SlowTower::getSlowTime()
{
	return slowTime;
}

float SlowTower::getSlowPower()
{
	return slowPower;
}

