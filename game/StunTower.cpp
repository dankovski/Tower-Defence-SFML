#include "StunTower.h"


StunTower::StunTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
	stunTime = getInitStunTime();
};

void StunTower::checkBulletsCollision(Enemy* mEnemyPointer)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isColliding(mEnemyPointer->getGlobalBounds())) {
			bullets.erase(bullets.begin() + i);
			mEnemyPointer->receiveDamage(damage);
			mEnemyPointer->startStun(stunTime);
			i--;
		}

	}

}

bool StunTower::hasEnemyInRange(std::shared_ptr<Enemy> mEnemy) {

	if (mEnemy->isStunned()) {
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

void StunTower::upgrade()
{
	level++;
	range.setRadius(range.getRadius() + 10);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	attackSpeed += 0.05;
	value += getUpgradeCost();
	stunTime += 0.05;
}



int StunTower::getInitValue()
{
	return 80;
}

int StunTower::getInitRange()
{
	return 300;
}

int StunTower::getInitDamage()
{
	return 0;
}

float StunTower::getInitAttackSpeed()
{
	return 0.5;
}

float StunTower::getInitStunTime()
{
	return 1.0;
}

float StunTower::getStunTime()
{
	return stunTime;
}
