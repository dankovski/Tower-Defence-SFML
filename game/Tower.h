#pragma once
#include "sfml/Graphics.hpp"
#include "Enemy.h"
#include <cmath>

class Tower
{
protected:
	sf::Sprite sprite;
	sf::CircleShape range;
	
	int level;
	bool isTowerSelected;
	int attackSpeed;
	double timeFromLastAttack;
	int damage;
	bool hasTarget;
	std::shared_ptr<Enemy> targetPointer;

public:
	
	Tower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mAttackSpeed);
	~Tower();
	virtual void render(double mDeltaTime) {};
	virtual void draw(sf::RenderWindow& mWindow);
	virtual void checkBulletsCollision(Enemy* mEnemyPointer) {};
	void drawRange(sf::RenderWindow& mWindow);
	bool hasEnemyTarget();
	bool hasEnemyInRange(sf::FloatRect mEnemyGlobalBounds);
	void setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy);
	bool isColliding(sf::Vector2f mMousePosition);
	bool isSelected();
	void setTowerSelected(bool mIsSelected);
	virtual void attack() {};
};

