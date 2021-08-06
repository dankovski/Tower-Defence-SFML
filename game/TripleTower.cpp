#include "TripleTower.h"


TripleTower::TripleTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getRange(), 5, 1.5) {
};

void TripleTower::attack()
{
	sf::Vector2f moveVector = targetPointer->getPosition() - sprite.getPosition();
	float angle = atan2(moveVector.y, moveVector.x);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(10 * cos(angle + 90), 20 * sin(angle + 90)), targetPointer->getPosition() + sf::Vector2f(20 * cos(angle + 90), 20 * sin(angle + 90)), 400.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition(), 400.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition() + sf::Vector2f(10 * cos(angle - 90), 20 * sin(angle - 90)), targetPointer->getPosition() + sf::Vector2f(20 * cos(angle - 90), 20 * sin(angle - 90)), 400.0));

}

int TripleTower::getValue()
{
	return 100;
}

int TripleTower::getRange()
{
	return 150;
}
