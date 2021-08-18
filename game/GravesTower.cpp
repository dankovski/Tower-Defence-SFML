#include "GravesTower.h"


GravesTower::GravesTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
};

void GravesTower::attack()
{
	
	sf::Vector2f moveVector = targetPointer->getPosition() - sprite.getPosition();
	float angle = atan2(moveVector.y, moveVector.x);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition()+ sf::Vector2f(10 * cos(angle + M_PI/2.0), 10 * sin(angle + M_PI / 2.0)), targetPointer->getPosition()+ sf::Vector2f(10 * cos(angle + M_PI / 2.0), 10 * sin(angle + M_PI / 2.0)), 700.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition()+ sf::Vector2f(-10 * cos(angle + M_PI / 2.0), -10 * sin(angle + M_PI / 2.0)), targetPointer->getPosition()+ sf::Vector2f(-10 * cos(angle + M_PI / 2.0), -10 * sin(angle + M_PI / 2.0)), 700.0));
}

void GravesTower::upgrade()
{
	level++;
	range.setRadius(range.getRadius() + 5);
	range.setOrigin(range.getGlobalBounds().width / 2, range.getGlobalBounds().height / 2);
	damage += 2;
	attackSpeed += 0.1;
	value += getUpgradeCost();
}


int GravesTower::getInitValue()
{
	return 100;
}

int GravesTower::getInitRange()
{
	return 200;
}

int GravesTower::getInitDamage()
{
	return 8;
}

float GravesTower::getInitAttackSpeed()
{
	return 1.5;
}

