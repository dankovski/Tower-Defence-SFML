#include "Enemy.h"

Enemy::Enemy(sf::Texture* mTexture, int mDamage, int mHp, float mSpeed, int mReward, std::vector<sf::Vector2f> mPathPoints, int mTextureFrames, float mAnimationDuration) {
	spritePointer = std::make_unique<sf::Sprite>();
	spritePointer->setTexture(*mTexture);
	walkAnimation = Animator(spritePointer.get(), mTextureFrames, mAnimationDuration, true);

	spritePointer->setOrigin(sf::Vector2f(spritePointer->getGlobalBounds().width / 2, spritePointer->getGlobalBounds().height / 2));
	spritePointer->setPosition(mPathPoints[0]);

	hpBar.setSize(sf::Vector2f(50, 5));
	hpBar.setFillColor(sf::Color::Green);
	hpBar.setPosition(sf::Vector2f(spritePointer->getPosition())+sf::Vector2f(-25, -40));
	hpBar.setOutlineThickness(2);
	hpBar.setOutlineColor(sf::Color::Black);

	maxHp = mHp;
	speed = mSpeed;
	pathIndex = 1;
	pathPoints = mPathPoints;
	direction = sf::Vector2f(pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x, pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y);
	direction = direction / (sqrt(direction.x * direction.x + direction.y * direction.y));
	hp = mHp;
	damage = mDamage;
	reward = mReward;
}

void Enemy::render(double mDeltaTime) {
	hpBar.setSize(sf::Vector2f((float)hp/maxHp*50,10));
	hpBar.setPosition(sf::Vector2f(spritePointer->getPosition()) + sf::Vector2f(-25, -40));


	if (pathIndex < pathPoints.size() &&
		( (pathPoints[pathIndex].x == pathPoints[pathIndex - 1].x && (
		( (pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y) > 0 && spritePointer->getPosition().y - pathPoints[pathIndex].y > 0) ||
		( (pathPoints[pathIndex].y - pathPoints[pathIndex - 1].y) < 0 && spritePointer->getPosition().y - pathPoints[pathIndex].y < 0) )) ||
		(pathPoints[pathIndex].y == pathPoints[pathIndex - 1].y && (
			((pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x) > 0 && spritePointer->getPosition().x - pathPoints[pathIndex].x > 0) ||
			((pathPoints[pathIndex].x - pathPoints[pathIndex - 1].x) < 0 && spritePointer->getPosition().x - pathPoints[pathIndex].x < 0) )) )) {
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
		spritePointer->setColor(sf::Color::Blue);
		if (timeFromLastStun >= stunTime) {
			isEnemyStunned = false;
		}
	}
	else if (isSlowed) {
		spritePointer->move(sf::Vector2f(0.5*direction.x * mDeltaTime * speed, 0.5*direction.y * mDeltaTime * speed));
		spritePointer->setColor(sf::Color::Green);
	}
	else {
		spritePointer->move(sf::Vector2f(direction.x * mDeltaTime * speed, direction.y * mDeltaTime * speed));
		spritePointer->setColor(sf::Color::White);
	}
	if (!isEnemyStunned) {
		walkAnimation.update(mDeltaTime);
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
	return spritePointer->getGlobalBounds();
}

sf::Vector2f Enemy::getPosition()
{
	return spritePointer->getPosition();
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

int Enemy::getRewardValue()
{
	return reward;
}

int Enemy::getDamageValue()
{
	return damage;
}


void Enemy::draw(sf::RenderWindow& mWindow) {
	mWindow.draw(*spritePointer.get());
	mWindow.draw(hpBar);
}