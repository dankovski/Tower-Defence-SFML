#pragma once
#include "sfml/Graphics.hpp"
#include "Enemy.h"

class Tower
{
private:
	sf::Sprite sprite;
	sf::CircleShape range;
	int damage;
	int level;
	unsigned long lastAttackTime;
	bool canAttack;
	bool isSelected;
	int shotSpeed;
	std::shared_ptr<Enemy> targetPointer;
	bool hasTarget;

public:
	Tower(sf::Texture* mTurretTexture, sf::Vector2f mPosition, int mRange, int mDamage, int mShotSpeed);
	~Tower();
	void render(unsigned long mDeltaTime);
	void draw(sf::RenderWindow& mWindow);
	bool hasEnemyTarget();
	bool hasEnemyInRange(sf::FloatRect mEnemyGlobalBounds);
	void setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy);
};

