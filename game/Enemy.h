#pragma once
#include "sfml/Graphics.hpp"
#include <iostream>

class Enemy
{
private:
	sf::Sprite sprite;
	int damage;
	int hp;
	float speed;
	int reward;
	std::vector<sf::Vector2f> pathPoints;
	int pathIndex;
	sf::Vector2f direction;

public:
	Enemy(sf::Texture* mTexture, int mDamage, int mHp, float mSpeed, int mReward, std::vector<sf::Vector2f> mPathPoints);
	void draw(sf::RenderWindow& mWindow);
	void render(double mDeltaTime);
	bool isAttacking();
	int getHp();
	sf::FloatRect getGlobalBounds();

};

