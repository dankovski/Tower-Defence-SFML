#pragma once
#include "sfml/Graphics.hpp"
#include <iostream>
#include <math.h>

class Bullet
{
private:
	sf::Sprite bulletSprite;
	sf::Vector2f moveVector;
	float moveSpeed;

public:
	Bullet(sf::Texture* mBulletTexture, sf::Vector2f mPosition, sf::Vector2f mEnemyPosition, float mMoveSpeed);
	void render(double mDeltaTime);
	void draw(sf::RenderWindow& mWindow);
	bool isColliding(sf::FloatRect mEnemyGlobalBounds);
	bool isOutOfMap();


};

