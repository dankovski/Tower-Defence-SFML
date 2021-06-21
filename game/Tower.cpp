#include "Tower.h"


Tower::Tower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mShotSpeed) {
	
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
	isSelected = true;
}


Tower::~Tower(){

}

void Tower::render(unsigned long mDeltaTime){
	if (hasTarget) {
		
		if (targetPointer->getHp() <= 0 || targetPointer->isAttacking() || !hasEnemyInRange(targetPointer->getGlobalBounds())) {
			hasTarget = false;
			targetPointer.reset();
		}
	//todo update rotation
	}
	else {
	
	}


}

void Tower::draw(sf::RenderWindow& mWindow) {
	mWindow.draw(sprite);
	
	if (isSelected) {
		mWindow.draw(range);
	}


}

bool Tower::hasEnemyTarget()
{
	return hasTarget;
}

bool Tower::hasEnemyInRange(sf::FloatRect mEnemyGlobalBounds)
{
	if (range.getGlobalBounds().intersects(mEnemyGlobalBounds)) {
		return true;
	}
	else {

	return false;
	}	
}

void Tower::setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy)
{
	hasTarget = true;
	targetPointer = mNewTargetEnemy;
}
