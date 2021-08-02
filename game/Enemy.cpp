#include "Enemy.h"

Enemy::Enemy(sf::Texture* mTexture, int mDamage, int mHp, float mSpeed, int mReward, std::vector<sf::Vector2f> mPathPoints) {

	sprite.setTexture(*mTexture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
	sprite.setPosition(mPathPoints[0]);
	speed = mSpeed;
	pathIndex = 1;
	pathPoints = mPathPoints;
	direction = sf::Vector2f(pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x, pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y);
	direction = direction / (sqrt(direction.x * direction.x + direction.y * direction.y));
	hp = mHp;
}



void Enemy::render(double mDeltaTime) {

	if (pathIndex < pathPoints.size() &&
		( (pathPoints[pathIndex].x == pathPoints[pathIndex - 1].x && (
		( (pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y) > 0 && sprite.getPosition().y - pathPoints[pathIndex].y > 0) ||
		( (pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y) < 0 && sprite.getPosition().y - pathPoints[pathIndex].y < 0) )) ||
		(pathPoints[pathIndex].y == pathPoints[pathIndex - 1].y && (
			((pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x) > 0 && sprite.getPosition().x - pathPoints[pathIndex].x > 0) ||
			((pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x) < 0 && sprite.getPosition().x - pathPoints[pathIndex].x < 0) )) )) {
	pathIndex++;
	if (pathIndex == pathPoints.size()) {
		direction = sf::Vector2f(0, 0);
	}
	else {
		direction = sf::Vector2f(pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x, pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y);
		direction = direction / (sqrt(direction.x * direction.x + direction.y * direction.y));
	}

	}


	sprite.move(sf::Vector2f(direction.x * mDeltaTime * speed, direction.y * mDeltaTime * speed));
	//std::cout << sprite.getPosition().x << "  " << sprite.getPosition().y << std::endl;
	//std::cout << double(mDeltaTime * speed) << std::endl;
}

bool Enemy::isAttacking()
{
	if (pathIndex == pathPoints.size()) {
		return true;
	}
	else {
		return false;
	}
}

int Enemy::getHp()
{
	return hp;
}

void Enemy::getDamage(int mDamage)
{
	hp = hp - mDamage;
	std::cout << "dmg:" << mDamage << std::endl;
	std::cout << "hp:" << hp << std::endl;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition()
{
	return sprite.getPosition();
}


void Enemy::draw(sf::RenderWindow& mWindow) {
	mWindow.draw(sprite);
}