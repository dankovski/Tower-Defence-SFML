#include "Bullet.h"

Bullet::Bullet(sf::Texture* mBulletTexture, sf::Vector2f mPosition, sf::Vector2f mEnemyPosition, float mMoveSpeed)
{
	moveSpeed = mMoveSpeed;

	bulletSprite.setTexture(*mBulletTexture);
	bulletSprite.setOrigin(bulletSprite.getGlobalBounds().width / 2, bulletSprite.getGlobalBounds().height / 2);
	bulletSprite.setPosition(mPosition);
	
	moveVector = mEnemyPosition - mPosition;
	float length = (sqrt(pow(moveVector.x, 2) + pow(moveVector.y, 2)));
	moveVector = sf::Vector2f(moveVector.x / length, moveVector.y / length);

	bulletSprite.setRotation(90 + 180.0 / 3.14 * atan2(moveVector.y, moveVector.x));
}

void Bullet::render(double mDeltaTime)
{
	bulletSprite.setPosition(bulletSprite.getPosition() + sf::Vector2f(mDeltaTime * moveSpeed * moveVector.x, mDeltaTime * moveSpeed * moveVector.y) );

}

void Bullet::draw(sf::RenderWindow& mWindow)
{
	mWindow.draw(bulletSprite);
}

bool Bullet::isColliding(sf::FloatRect mEnemyGlobalBounds)
{
	if (bulletSprite.getGlobalBounds().intersects(mEnemyGlobalBounds)) {
		return true;
	}
	else {
		return false;
	}
}

bool Bullet::isOutOfMap()
{
	if (bulletSprite.getPosition().x > 1100 || bulletSprite.getPosition().x < -100 || bulletSprite.getPosition().y > 1100 || bulletSprite.getPosition().y < -100) {
		return true;
	}
	else {
		return false;
	}

}
