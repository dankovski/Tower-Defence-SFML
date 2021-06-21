#pragma once
#include <fstream>
#include <iostream>
#include "sfml/Graphics.hpp"
#include "Tile.h"
#include <memory>

class GameMap
{
public:
	GameMap();
	GameMap(int width, int height);
	~GameMap();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getCenterOfTile(sf::Vector2f mMousePosition);
	bool isTileAvailable(sf::Vector2f mMousePosition);
	void setTileType(sf::Vector2f mMousePosition, bool mType);
	std::vector<sf::Vector2f> getPathPoints();

private:
	int widthMap;
	int heightMap;
	Tile tileArray[20][20];

	std::vector<sf::Vector2f> mapPathPoints;


	std::shared_ptr<sf::Texture> castleTexture;
	std::shared_ptr<sf::Texture> curveBiggerTexture1;
	std::shared_ptr<sf::Texture> curveBiggerTexture2;
	std::shared_ptr<sf::Texture> curveSmallerTexture1;
	std::shared_ptr<sf::Texture> curveSmallerTexture2;
	std::shared_ptr<sf::Texture> sideTexture1;
	std::shared_ptr<sf::Texture> sideTexture2;
	std::shared_ptr<sf::Texture> solidTowerTexture;
	std::shared_ptr<sf::Texture> solidMonsterTexture;

	void loadMap();



};

