#pragma once
#include "sfml/Graphics.hpp"
#include <iostream>
#include "Animator.h"

class Enemy
{
private:
	std::unique_ptr<sf::Sprite> spritePointer;
	int damage;
	int hp;
	int maxHp;
	float speed;
	int reward;
	std::vector<sf::Vector2f> pathPoints;
	int pathIndex;
	sf::Vector2f direction;
	bool isEnemyStunned = false;
	double timeFromLastStun;
	double stunTime;
	sf::RectangleShape hpBar;
	bool isSlowed = false;

	Animator walkAnimation;

public:
	Enemy(sf::Texture* mTexture, int mDamage, int mHp, float mSpeed, int mReward, std::vector<sf::Vector2f> mPathPoints, int mTextureFrames, float mAnimationDuration);
	void draw(sf::RenderWindow& mWindow);
	void render(double mDeltaTime);
	bool isAttacking();
	int getHp();
	void receiveDamage(int mDamage);
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	void startStun(double mStunTime);
	bool isStunned();
	int getRewardValue();
	int getDamageValue();

};

