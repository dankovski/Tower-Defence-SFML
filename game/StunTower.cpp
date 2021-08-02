#include "StunTower.h"


StunTower::StunTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, 200, 5, 0.5) {
	stunTime = 1.0;
};

void StunTower::checkBulletsCollision(Enemy* mEnemyPointer)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isColliding(mEnemyPointer->getGlobalBounds())) {
			bullets.erase(bullets.begin() + i);
			mEnemyPointer->receiveDamage(damage);
			mEnemyPointer->startStun(1.0);
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