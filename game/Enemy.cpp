#include "Enemy.h"

Enemy::Enemy(sf::Texture* mTexture, int mDamage, int mHp, float mSpeed, int mReward, std::vector<sf::Vector2f> mPathPoints) {
	sprite.setTexture(*mTexture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
	sprite.setPosition(mPathPoints[0]);

	hpBar.setSize(sf::Vector2f(50, 10));
	hpBar.setFillColor(sf::Color::Green);
	hpBar.setPosition(sf::Vector2f(sprite.getPosition())+sf::Vector2f(-25, -40));
	maxHp = mHp;
	speed = mSpeed;
	pathIndex = 1;
	pathPoints = mPathPoints;
	direction = sf::Vector2f(pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x, pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y);
	direction = direction / (sqrt(direction.x * direction.x + direction.y * direction.y));
	hp = mHp;
}



void Enemy::render(double mDeltaTime) {
	hpBar.setSize(sf::Vector2f((float)hp/maxHp*50,10));
	hpBar.setPosition(sf::Vector2f(sprite.getPosition()) + sf::Vector2f(-25, -40));

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

	if (isEnemyStunned) {
		timeFromLastStun += mDeltaTime;
		sprite.setColor(sf::Color::Blue);
		if (timeFromLastStun >= stunTime) {
			isEnemyStunned = false;
		}
	}
	else if (isSlowed) {
		sprite.move(sf::Vector2f(0.5*direction.x * mDeltaTime * speed, 0.5*direction.y * mDeltaTime * speed));
		sprite.setColor(sf::Color::Green);
	}
	else {
		sprite.setColor(sf::Color::White);
		sprite.move(sf::Vector2f(direction.x * mDeltaTime * speed, direction.y * mDeltaTime * speed));
	}
	

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

void Enemy::receiveDamage(int mDamage)
{
	hp = hp - mDamage;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition()
{
	return sprite.getPosition();
}

void Enemy::startStun(double mStunTime)
{
	isEnemyStunned = true;
	timeFromLastStun = 0.0;
	stunTime = mStunTime;
}

bool Enemy::isStunned()
{
	return isEnemyStunned;
}


void Enemy::draw(sf::RenderWindow& mWindow) {
	mWindow.draw(sprite);
	mWindow.draw(hpBar);
}