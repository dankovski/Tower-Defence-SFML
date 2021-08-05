#pragma once
#include "sfml/Graphics.hpp"
#include "TurretHUD.h"
#include <iostream>

class GameHUD
{
public:
	GameHUD(sf::Vector2f mBackgroundSize, sf::Vector2f mPosition, sf::Vector2f mTurretSize, std::vector<std::shared_ptr<sf::Texture>> mTurretsTextures);
	GameHUD();
	void draw(sf::RenderWindow& window);
	void render(int mPlayerGold, sf::Vector2f mMousePosition, bool mIsAvailable);
	void setPosition(int width, int height);
	int getTurretsVectorSize();
	bool checkTurretCollision(sf::Vector2f mMousePosition, int mTurretNumber);
	void setTurretClicked(int mTurretNumber);
	void setTurretsUnclicked();
	bool isAnyTurretsClicked();
	bool isClickedTurretAvailable();
	int GameHUD::getTurretClcikedNumber();

private:
	sf::RectangleShape background;

	sf::Text pointsText;
	sf::Text hpText;

	std::unique_ptr<sf::Texture> coinTexture;
	std::unique_ptr<sf::Font> font;

	std::vector<TurretHUD> turretsVector;
	std::vector<std::shared_ptr<sf::Texture>> turretsTexturesVector;
	bool isTurretClicked;
	int clickedTurretNumber;

};

