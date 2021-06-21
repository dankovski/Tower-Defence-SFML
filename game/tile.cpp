#include "Tile.h"
#include <iostream>



Tile::~Tile() {

}

Tile::Tile() {
	isAvailable = true;
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Tile::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Tile::setTexture(sf::Texture texture) {
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Tile::setTexture(std::shared_ptr<sf::Texture> texture){
	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Tile::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
}

void Tile::setRotation(int rotation) {
	sprite.setRotation(rotation);
}


sf::Vector2f Tile::getPosition() {

	return sprite.getPosition();
}

bool Tile::isColliding(sf::Vector2f mMousePosition) {
	if (sprite.getGlobalBounds().contains(mMousePosition.x, mMousePosition.y)) {
		return true;
	}
	else {
		return false;
	}
}

void Tile::setAvailable(bool mIsAvailable) {
	isAvailable = mIsAvailable;
}

bool Tile::isTileAvailable() {
	return isAvailable;
}

