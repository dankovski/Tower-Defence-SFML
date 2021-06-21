#pragma once
#include "sfml/Graphics.hpp"
#include <memory>

class Tile
{
public:
	Tile();
	~Tile();
	void draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	void setTexture(sf::Texture texture);
	void setTexture(std::shared_ptr<sf::Texture> texture);
	void setRotation(int rotation);
	sf::Vector2f Tile::getPosition();
	bool isColliding(sf::Vector2f mMousePosition);
	bool isTileAvailable();
	void setAvailable(bool mIsAvailable);
private:
	bool isAvailable;
	sf::Sprite sprite;

};

