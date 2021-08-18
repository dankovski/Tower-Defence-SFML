#include "Tower.h"


Tower::Tower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition, int mRange, int mDamage, float mAttackSpeed, int mValue) {
	
	range.setRadius(mRange);
	range.setOutlineThickness(5);
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Cyan);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	range.setPosition(mPosition);



	sprite.setTexture(*mTurretTexture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(mPosition);

	background.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	background.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	background.setPosition(mPosition); 
	background.setFillColor(sf::Color::Cyan);

	hasTarget = false;
	isTowerSelected = false;

	value = mValue;
	bulletTexture = mBulletTexture;
	level = 1;
	timeFromLastAttack = 1.0 / mAttackSpeed;
	attackSpeed = mAttackSpeed;
	damage = mDamage;

}

Tower::~Tower(){

}

void Tower::drawRange(sf::RenderWindow& mWindow) {
	if (isTowerSelected) {
		mWindow.draw(range);
	}
}

bool Tower::hasEnemyTarget()
{
	return hasTarget;
}

bool Tower::canUpgrade()
{
	if (level < 10) {
		return true;
	}
	else {
		return false;
	}
	
}

bool Tower::hasEnemyInRange(std::shared_ptr<Enemy> mEnemy){

	sf::FloatRect mEnemyGlobalBounds = mEnemy->getGlobalBounds();
	float xDistance = abs(range.getPosition().x - (mEnemyGlobalBounds.left + mEnemyGlobalBounds.width / 2.0));
	float yDistance = abs(range.getPosition().y - (mEnemyGlobalBounds.top + mEnemyGlobalBounds.height / 2.0));

	if (xDistance > (mEnemyGlobalBounds.width / 2.0 + range.getRadius())) { return false; }
	if (yDistance > (mEnemyGlobalBounds.height / 2.0 + range.getRadius())) { return false; }

	if (xDistance <= (mEnemyGlobalBounds.width / 2.0)) { return true; }
	if (yDistance <= (mEnemyGlobalBounds.height / 2.0)) { return true; }

	return (sqrt(pow((xDistance - mEnemyGlobalBounds.width / 2.0), 2.0) + pow((yDistance - mEnemyGlobalBounds.height / 2.0), 2)) <= range.getRadius() );
}

void Tower::setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy)
{
	hasTarget = true;
	targetPointer = mNewTargetEnemy;
}

bool Tower::isColliding(sf::Vector2f mMousePosition) {
	if (sprite.getGlobalBounds().contains(mMousePosition.x, mMousePosition.y)) {
		return true;
	}
	else {
		return false;
	}
}

bool Tower::isSelected()
{
	return isTowerSelected;
}

void Tower::setTowerSelected(bool mIsSelected)
{
	isTowerSelected = mIsSelected;
}

void Tower::draw(sf::RenderWindow& mWindow)
{


	if (isTowerSelected) {
		mWindow.draw(background);
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw(mWindow);
	}

	mWindow.draw(sprite);
}

void Tower::checkBulletsCollision(Enemy* mEnemyPointer)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isColliding(mEnemyPointer->getGlobalBounds())) {
			bullets.erase(bullets.begin() + i);
			mEnemyPointer->receiveDamage(damage);
			i--;
		}

	}

}

void Tower::upgrade()
{
	level++;
	range.setRadius(range.getRadius() + 10);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	damage += 2;
	attackSpeed += 0.1;
	value += getUpgradeCost();
}

int Tower::getUpgradeCost()
{
	return value/2;
}

int Tower::getLevel()
{
	return level;
}

int Tower::getDamage()
{
	return damage;
}

int Tower::getRange()
{
	return range.getRadius();
}

float Tower::getAttackSpeed()
{
	return attackSpeed;
}

int Tower::getValue()
{
	return value;
}

sf::Vector2f Tower::getPosition()
{
	return sprite.getPosition();
}

void Tower::render(double mDeltaTime) {

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

		if (targetPointer->getHp() <= 0 || targetPointer->isAttacking() || !hasEnemyInRange(targetPointer)) {
			hasTarget = false;
			targetPointer.reset();
		}

	}


}

void Tower::attack()
{
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition(), 1500.0));
}


