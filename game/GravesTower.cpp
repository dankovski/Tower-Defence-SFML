#include "GravesTower.h"


GravesTower::GravesTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture, mPosition, getRange(), 10, 2.0) {
};

void GravesTower::attack()
{
	sf::Vector2f moveVector = targetPointer->getPosition() - sprite.getPosition();
	float angle = atan2(moveVector.y, moveVector.x);
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition() + sf::Vector2f(100 * cos(angle + 90), 100 * sin(angle + 90)), 500.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition(), 500.0));
	bullets.push_back(Bullet(bulletTexture, sprite.getPosition(), targetPointer->getPosition() + sf::Vector2f(100 * cos(angle - 90), 100 * sin(angle - 90)), 500.0));

}

int GravesTower::getValue()
{
	return 100;
}

int GravesTower::getRange()
{
	return 200;
}
