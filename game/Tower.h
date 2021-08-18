#pragma once
#include "sfml/Graphics.hpp"
#include "Enemy.h"
#include <cmath>
#include "Bullet.h"
#include <iostream>

#define M_PI (3.14159265358979323846)
class Tower
{
protected:
	sf::Sprite sprite;
	sf::CircleShape range;
	int level;
	bool isTowerSelected;
	float attackSpeed;
	double timeFromLastAttack;
	int damage;
	bool hasTarget;
	std::shared_ptr<Enemy> targetPointer;
	std::vector<Bullet> bullets;
	sf::Texture* bulletTexture;
	int value;
	sf::RectangleShape background;

public:
	
	Tower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition, int mRange, int mDamage, float mAttackSpeed, int mValue);
	~Tower();
	void render(double mDeltaTime);
	void draw(sf::RenderWindow& mWindow);
	void drawRange(sf::RenderWindow& mWindow);
	bool hasEnemyTarget();
	bool canUpgrade();
	virtual bool hasEnemyInRange(std::shared_ptr<Enemy> mEnemy);
	void setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy);
	bool isColliding(sf::Vector2f mMousePosition);
	bool isSelected();
	void setTowerSelected(bool mIsSelected);
	virtual void attack();
	virtual void checkBulletsCollision(Enemy* mEnemyPointer);
	virtual void upgrade();
	int getUpgradeCost();
	int getLevel();
	int getDamage();
	int getRange();
	float getAttackSpeed();
	int getValue();
	virtual float getStunTime() { return 0.0; };
	virtual float getSlowTime() { return 0.0; };
	virtual float getSlowPower() { return 0.0; };
	sf::Vector2f getPosition();
};

