#pragma once
#include "sfml/Graphics.hpp"
#include "Enemy.h"
#include <cmath>
#include "Bullet.h"

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

public:
	
	Tower(sf::Texture* mTurretTexture, sf::Texture* mBulletTexture, sf::Vector2f mPosition, int mRange, int mDamage, float mAttackSpeed);
	~Tower();
	void render(double mDeltaTime);
	void draw(sf::RenderWindow& mWindow);
	void drawRange(sf::RenderWindow& mWindow);
	bool hasEnemyTarget();
	virtual bool hasEnemyInRange(std::shared_ptr<Enemy> mEnemy);
	void setTargetEnemy(std::shared_ptr<Enemy> mNewTargetEnemy);
	bool isColliding(sf::Vector2f mMousePosition);
	bool isSelected();
	void setTowerSelected(bool mIsSelected);
	virtual void attack();
	virtual void checkBulletsCollision(Enemy* mEnemyPointer);

};

