#include "TripleTower.h"


TripleTower::TripleTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
};

void TripleTower::attack()
{
	sf::Vector2f moveVector = targetPointer->getPosition() - sprite.getPosition();
	float angle = atan2(moveVector.y, moveVector.x);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(20 * cos(angle + M_PI / 2.0), 20 * sin(angle + M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(20 * cos(angle + M_PI / 2.0), 20 * sin(angle + M_PI / 2.0)), 700.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition(), 700.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(20 * cos(angle - M_PI / 2.0), 20 * sin(angle - M_PI / 2.0)), targetPointer->getPosition() + sf::Vector2f(20 * cos(angle - M_PI / 2.0), 20 * sin(angle - M_PI / 2.0)), 700.0));

}

int TripleTower::getInitValue()
{
	return 100;
}

int TripleTower::getInitRange()
{
	return 150;
}

int TripleTower::getInitDamage()
{
	return 8;
}

float TripleTower::getInitAttackSpeed()
{
	return 0.8;
}
