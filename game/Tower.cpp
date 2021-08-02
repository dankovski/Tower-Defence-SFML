#include "Tower.h"

Tower::Tower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mAttackSpeed) {
	
	range.setRadius(mRange);
	range.setOutlineThickness(5);
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Cyan);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	range.setPosition(mPosition);

	sprite.setTexture(*mTurretTexture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(mPosition);
	hasTarget = false;
	isTowerSelected = false;

	attackSpeed = mAttackSpeed;
	damage = mDamage;

}

Tower::~Tower(){

}

void Tower::draw(sf::RenderWindow& mWindow) {
	mWindow.draw(sprite);
	
	if (isTowerSelected) {
		mWindow.draw(range);
	}


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

bool Tower::hasEnemyInRange(sf::FloatRect mEnemyGlobalBounds)
{
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
