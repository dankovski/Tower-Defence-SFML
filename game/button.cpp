#include "Button.h"
#include <iostream>

Button::Button(sf::Font* buttonFont, std::string string, sf::Vector2f position, int characterSize, sf::Color color) {

	text.setFont(*buttonFont);
	text.setFillColor(color);
	text.setString(string);
	text.setCharacterSize(characterSize);
	text.setOutlineThickness(5);
	text.setOutlineColor(sf::Color::Black);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(position);

	rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
	rectangle.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2));
	rectangle.setPosition(sf::Vector2f(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2));

	collision = rectangle.getGlobalBounds();
	haveSprite = false;
	haveText = true;
}

Button::Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size) {

	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(position);
	sprite.setScale(size.x / (*texture).getSize().x, size.y / (*texture).getSize().y);
	collision = sprite.getGlobalBounds();
	haveSprite = true;
	haveText = false;
}

bool Button::isColliding(sf::Vector2f mousePosition) {
	
	if (collision.contains(mousePosition.x, mousePosition.y)) {
		return true;
	}
	else {
		return false;
	}

}

bool Button::isColliding(sf::Vector2i mousePosition) {
	if (collision.contains(mousePosition.x, mousePosition.y)) {
		return true;
	}
	else {
		return false;
	}

}

void Button::draw(sf::RenderWindow& window) {
	//window.draw(rectangle);
	
	if (haveSprite) { window.draw(sprite); collision = sprite.getGlobalBounds();
	}
	if (haveText) { window.draw(text); collision = rectangle.getGlobalBounds();}
	
}

void Button::setTextSize(int size) {
	text.setCharacterSize(size);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
	rectangle.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2));
	rectangle.setPosition(sf::Vector2f(text.getGlobalBounds().left+ text.getGlobalBounds().width / 2, text.getGlobalBounds().top+ text.getGlobalBounds().height / 2));
	collision = rectangle.getGlobalBounds();
}

void Button::setTextColor(sf::Color textColor) {
	text.setFillColor(textColor);
}

void Button::setPosition(sf::Vector2f pos) {

	if (haveText) {
		text.setPosition(pos);
		rectangle.setPosition(sf::Vector2f(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2));
		collision = rectangle.getGlobalBounds();
	}
	if (haveSprite) {
		sprite.setPosition(pos);
		collision = sprite.getGlobalBounds();
	}
}

void Button::changeText(std::string mNewText)
{
	text.setString(mNewText);
	text.setOrigin(text.getGlobalBounds().width / 2.0, text.getGlobalBounds().height / 2.0);
	rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
	rectangle.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2.0, text.getGlobalBounds().height / 2.0));
	collision = rectangle.getGlobalBounds();
}


