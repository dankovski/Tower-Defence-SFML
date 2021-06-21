#pragma once
#include "sfml/Graphics.hpp"

class TurretHUD
{
private:
	sf::Sprite turretSprite;
	sf::Text goldText;
	sf::Sprite coinSprite;
	sf::RectangleShape backgroundRectangle;
	sf::CircleShape turretRangeCircle; 
	int goldValue;
	int turretRange;
	bool isClicked;
	bool isAvailable;
	sf::Vector2f initPosition;

public:
	TurretHUD();
	TurretHUD(sf::Font* mFont, sf::Texture* mTurretTexture, sf::Texture* mCoinTexture, sf::Vector2f mPosition, sf::Vector2f mTurretSize, int mGoldValue, int mTurretRange);
	void setPosition(sf::Vector2f mPosition);
	bool isColliding(sf::Vector2f mMousePosition);
	void draw(sf::RenderWindow& window);
	void render(int mPlayerGold, sf::Vector2f mMousePosition, bool mIsAvailable);
	void setClicked(bool mIsClicked);
	bool isTurretClicked();
	bool isTurretAvailable();
};

