#include "SuperTower.h"


SuperTower::SuperTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
};

void SuperTower::attack()
{
	sf::Vector2f moveVector = targetPointer->getPosition() - sprite.getPosition();
	float angle = atan2(moveVector.y, moveVector.x);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(8 * cos(angle + M_PI / 2.0), 8 * sin(angle + M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(8 * cos(angle + M_PI / 2.0), 8 * sin(angle + M_PI / 2.0)), 600.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(-8 * cos(angle + M_PI / 2.0), -8 * sin(angle + M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(-8 * cos(angle + M_PI / 2.0), -8 * sin(angle + M_PI / 2.0)), 600.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(20 * cos(angle + M_PI / 2.0), 20 * sin(angle + M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(20 * cos(angle + M_PI / 2.0), 20 * sin(angle + M_PI / 2.0)), 600.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(-20 * cos(angle + M_PI / 2.0), -20 * sin(angle + M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(-20 * cos(angle + M_PI / 2.0), -20 * sin(angle + M_PI / 2.0)), 600.0));
}

int SuperTower::getInitValue()
{
	return 200;
}

int SuperTower::getInitRange()
{
	return 200;
}

int SuperTower::getInitDamage()
{
	return 10;
}

float SuperTower::getInitAttackSpeed()
{
	return 2.0;
}


