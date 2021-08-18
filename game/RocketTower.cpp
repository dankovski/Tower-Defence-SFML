#include "RocketTower.h"


RocketTower::RocketTower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition) :
	Tower(mTurretTexture, mBulletTexture,  mPosition, getInitRange(), getInitDamage(), getInitAttackSpeed(), getInitValue()) {
}
int RocketTower::getInitValue()
{
	return 60;
}
int RocketTower::getInitRange()
{
	return 250;
}
int RocketTower::getInitDamage()
{
	return 8;
}
float RocketTower::getInitAttackSpeed()
{
	return 3.0;
}
;





