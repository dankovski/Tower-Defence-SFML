#pragma once

#include "sfml/Graphics.hpp"
class Button
{
public:
	Button(sf::Font* buttonFont, std::string string, sf::Vector2f position, int characterSize, sf::Color color);
	Button(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	bool isColliding(sf::Vector2f mousePosition);
	bool isColliding(sf::Vector2i mousePosition);
	void draw(sf::RenderWindow& window);
	void setTextSize(int size);
	void setTextColor(sf::Color textColor);
	void setPosition(sf::Vector2f pos);

private:
	bool haveText;
	bool haveSprite;
	sf::Text text;
	sf::FloatRect collision;
	sf::Font font;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;
};


