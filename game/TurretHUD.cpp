#include "turretHUD.h"
#include <iostream>
TurretHUD::TurretHUD() {



}


TurretHUD::TurretHUD(sf::Font* mFont, sf::Texture* mTurretTexture, sf::Texture* mCoinTexture, sf::Vector2f mPosition, sf::Vector2f mTurretSize, int mGoldValue, int mTurretRange) {
	
	isClicked = false;
	goldValue = mGoldValue; 
	turretSprite.setTexture(*mTurretTexture);
	turretSprite.setScale(mTurretSize.x / (float)(*mTurretTexture).getSize().x, (float)mTurretSize.y / (*mTurretTexture).getSize().y);
	turretSprite.setOrigin((turretSprite.getGlobalBounds().left + turretSprite.getGlobalBounds().width) / 2, mTurretSize.y / 2);

	backgroundRectangle.setSize(sf::Vector2f(mTurretSize.x, mTurretSize.y * 1.5));
	backgroundRectangle.setFillColor(sf::Color::Red);
	backgroundRectangle.setOrigin(0, 0);
	
	goldText.setFont(*mFont);
	goldText.setString(std::to_string(goldValue));
	goldText.setFillColor(sf::Color::Yellow);
	goldText.setCharacterSize(mTurretSize.x * 0.3);
	goldText.setOutlineThickness(3);
	goldText.setOutlineColor(sf::Color::Black);
	goldText.setOrigin(goldText.getGlobalBounds().width / 2, goldText.getGlobalBounds().height / 2);

	coinSprite.setTexture(*mCoinTexture);
	coinSprite.setOrigin(coinSprite.getGlobalBounds().width / 2, coinSprite.getGlobalBounds().height / 2);
	coinSprite.setScale(goldText.getGlobalBounds().height / (float)(*mCoinTexture).getSize().x, goldText.getGlobalBounds().height / (*mCoinTexture).getSize().y);

	turretRangeCircle.setRadius(mTurretRange);
	turretRangeCircle.setOutlineThickness(5);
	turretRangeCircle.setFillColor(sf::Color::Transparent);
	turretRangeCircle.setOutlineColor(sf::Color::Cyan);
	turretRangeCircle.setOrigin(turretRangeCircle.getGlobalBounds().width / 2, turretRangeCircle.getGlobalBounds().height / 2);

	initPosition = mPosition;
	this->setPosition(mPosition);
}

void TurretHUD::setPosition(sf::Vector2f mPosition) {
	turretSprite.setPosition(mPosition);
	backgroundRectangle.setPosition(sf::Vector2f(turretSprite.getGlobalBounds().left, turretSprite.getGlobalBounds().top));
	goldText.setPosition(sf::Vector2f(turretSprite.getGlobalBounds().left + turretSprite.getGlobalBounds().width * 0.7, turretSprite.getGlobalBounds().top + turretSprite.getGlobalBounds().height + goldText.getGlobalBounds().height / 2));
	coinSprite.setPosition(sf::Vector2f(turretSprite.getGlobalBounds().left + turretSprite.getGlobalBounds().width * 0.2, goldText.getGlobalBounds().top + goldText.getGlobalBounds().height / 2));
	turretRangeCircle.setPosition(mPosition);
}


void TurretHUD::draw(sf::RenderWindow& window) {
	//window.draw(backgroundRectangle);
	window.draw(turretSprite);

	if (isClicked) {
	window.draw(turretRangeCircle);
	}
	else {
	window.draw(goldText);
	window.draw(coinSprite);
	}

}


void TurretHUD::render(int mPlayerGold, sf::Vector2f mMousePosition, bool mIsAvailable) {

	if (!isClicked) {
		turretSprite.setPosition(initPosition);
		if (mPlayerGold >= goldValue) {
			goldText.setFillColor(sf::Color::Green);
			isAvailable = true;
		}
		else {
			goldText.setFillColor(sf::Color::Red);
			isAvailable = false;
		}
	}
	else {

		if (mIsAvailable) {
			turretRangeCircle.setOutlineColor(sf::Color::Cyan);
			isAvailable = true;
		}
		else {
			turretRangeCircle.setOutlineColor(sf::Color::Red);
			isAvailable = false;
		}

		turretSprite.setPosition(sf::Vector2f(mMousePosition.x, mMousePosition.y));
		turretRangeCircle.setPosition(sf::Vector2f(mMousePosition.x, mMousePosition.y));
	}
}

bool TurretHUD::isColliding(sf::Vector2f mMousePosition) {
	if (turretSprite.getGlobalBounds().contains(mMousePosition.x, mMousePosition.y) && !isClicked) {
		return true;
	}
	else {
		return false;
	}
}

void TurretHUD::setClicked(bool mIsClicked) {
	if (mIsClicked && isAvailable) {
		isClicked = true;
	}
	else {
		isClicked = false;
	}

}

bool TurretHUD::isTurretClicked() {
	return isClicked;
}

bool TurretHUD::isTurretAvailable() {
	return isAvailable;
}