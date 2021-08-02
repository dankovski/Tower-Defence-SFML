#include "RocketTower.h"


RocketTower::RocketTower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mAttackSpeed, sf::Texture* mBulletTexture) :
	Tower(mTurretTexture, mPosition, mRange, mDamage, mAttackSpeed) {
	bulletTexture = mBulletTexture;
};

void RocketTower::attack()
{
	//targetPointer->getDamage(damage);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition(), 1500.0));
}

void RocketTower::render(double mDeltaTime) {

	timeFromLastAttack += mDeltaTime;

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].render(mDeltaTime);
		if (bullets[i].isOutOfMap()) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}


	if (hasTarget) {
		if (timeFromLastAttack >= 1.0 / attackSpeed) {
			attack();
			timeFromLastAttack = 0.0;
		}
		
		sf::Vector2f moveVector = sprite.getPosition() - targetPointer->getPosition();
		sprite.setRotation(-90 + 180.0 / 3.14 * atan2(moveVector.y, moveVector.x));

		if (targetPointer->getHp() <= 0 || targetPointer->isAttacking() || !hasEnemyInRange(targetPointer->getGlobalBounds())) {
			hasTarget = false;
			targetPointer.reset();
		}


	}
	else {

	}

}

void RocketTower::checkBulletsCollision(Enemy* mEnemyPointer)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isColliding(mEnemyPointer->getGlobalBounds())) {
			bullets.erase(bullets.begin()+i);
			mEnemyPointer->getDamage(damage);
			i--;
		}
	
	}

}



void RocketTower::draw(sf::RenderWindow& mWindow)
{

		mWindow.draw(sprite);

		if (isTowerSelected) {
			mWindow.draw(range);
		}
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].draw(mWindow);
		}

}
