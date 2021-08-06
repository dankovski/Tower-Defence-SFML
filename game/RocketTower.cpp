#include "RocketTower.h"


RocketTower::RocketTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture,  mPosition, getRange(), 30, 1.0) {
}
int RocketTower::getValue()
{
	return 60;
}
int RocketTower::getRange()
{
	return 250;
}
;





