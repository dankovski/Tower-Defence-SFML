#include "gameHUD.h"

GameHUD::GameHUD() {
	background.setSize(sf::Vector2f(100, 100));
}


GameHUD::GameHUD(sf::Vector2f mBackgroundSize, sf::Vector2f mPosition, sf::Vector2f mTurretSize) {
	background.setSize(sf::Vector2f(mBackgroundSize.x, mBackgroundSize.y));
	background.setPosition(mPosition);
	background.setFillColor(sf::Color::Blue);
	isTurretClicked = false;
	font = std::make_unique<sf::Font>();
	coinTexture = std::make_unique<sf::Texture>();

	if (!(*font).loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo 8.ttf" << std::endl;
	}

	if (!(*coinTexture).loadFromFile("images/coin.png"))
	{
		std::cout << "nie wczytalo coin.png" << std::endl;
	}


	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[0]->loadFromFile("images/tower1.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[1]->loadFromFile("images/tower2.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[2]->loadFromFile("images/tower3.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[3]->loadFromFile("images/tower4.png");


	turretsVector.push_back(TurretHUD(font.get(), turretsTexturesVector[0].get(), coinTexture.get(),  sf::Vector2f(mPosition.x+mBackgroundSize.x / 3, mPosition.y+mBackgroundSize.y/6), sf::Vector2f(mTurretSize.x, mTurretSize.y), 80, 200));
	turretsVector.push_back(TurretHUD(font.get(), turretsTexturesVector[1].get(), coinTexture.get(), sf::Vector2f(mPosition.x+mBackgroundSize.x * 2 / 3, mPosition.y+mBackgroundSize.y/6), sf::Vector2f(mTurretSize.x, mTurretSize.y), 120, 300));
	turretsVector.push_back(TurretHUD(font.get(), turretsTexturesVector[2].get(), coinTexture.get(), sf::Vector2f(mPosition.x + mBackgroundSize.x / 3, mPosition.y + mBackgroundSize.y *2/ 6), sf::Vector2f(mTurretSize.x, mTurretSize.y), 100, 200));
	turretsVector.push_back(TurretHUD(font.get(), turretsTexturesVector[3].get(), coinTexture.get(), sf::Vector2f(mPosition.x + mBackgroundSize.x * 2 / 3, mPosition.y + mBackgroundSize.y*2 / 6), sf::Vector2f(mTurretSize.x, mTurretSize.y), 50, 300));


}


void GameHUD::draw(sf::RenderWindow& window) {

	window.draw(background);
	int clicked = -1;


	for (int i = 0; i < turretsVector.size(); i++) {
		if (!turretsVector[i].isTurretClicked()) {
			turretsVector[i].draw(window);
		}
		else {
			clicked = i;
			isTurretClicked = true;
		}
	}

	if (clicked >= 0) {
		turretsVector[clicked].draw(window);
	}

	
}

void GameHUD::render(int mPlayerGold, sf::Vector2f mMousePosition, bool mIsAvailable) {
	for (int i = 0; i < turretsVector.size(); i++) {
		turretsVector[i].render(mPlayerGold, mMousePosition, mIsAvailable);
	}
}

void GameHUD::setPosition(int width, int height) {
	background.setPosition(sf::Vector2f(width, height));
}

int GameHUD::getTurretsVectorSize() {
	return turretsVector.size();
}

bool GameHUD::checkTurretCollision(sf::Vector2f mMousePosition, int mTurretNumber) {
	return turretsVector[mTurretNumber].isColliding(mMousePosition);
}

void GameHUD::setTurretClicked(int mTurretNumber) {
	setTurretsUnclicked();
	turretsVector[mTurretNumber].setClicked(true);
	isTurretClicked = true;
	clickedTurretNumber = mTurretNumber;
}

void GameHUD::setTurretsUnclicked() {
	for (int i = 0; i < turretsVector.size(); i++) {
		turretsVector[i].setClicked(false);
	}
	isTurretClicked = false;

}

bool GameHUD::isAnyTurretsClicked() {

	return isTurretClicked;

}

int GameHUD::getTurretClcikedNumber() {

	return clickedTurretNumber;
}

bool GameHUD::isClickedTurretAvailable() {
	return turretsVector[clickedTurretNumber].isTurretAvailable();
}

