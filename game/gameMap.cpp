#include "gameMap.h"

GameMap::GameMap(int width, int height) {
	widthMap = width;
	heightMap = height;
	loadMap();
}


GameMap::~GameMap() {
	std::cout << "destructor map" << std::endl;
}


void GameMap::loadMap() {

	castleTexture = std::make_shared<sf::Texture>(); 
	curveSmallerTexture1 = std::make_shared<sf::Texture>();
	curveSmallerTexture2 = std::make_shared<sf::Texture>();
	curveBiggerTexture1 = std::make_shared<sf::Texture>();
	curveBiggerTexture2 = std::make_shared<sf::Texture>();
	sideTexture1 = std::make_shared<sf::Texture>();
	sideTexture2 = std::make_shared<sf::Texture>();
	solidTowerTexture = std::make_shared<sf::Texture>();
	solidMonsterTexture = std::make_shared<sf::Texture>();

	if (!castleTexture->loadFromFile("images/map1/castle.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!curveBiggerTexture1->loadFromFile("images/map1/curveBigger1.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!curveBiggerTexture2->loadFromFile("images/map1/curveBigger2.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!curveSmallerTexture1->loadFromFile("images/map1/curveSmaller1.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!curveSmallerTexture2->loadFromFile("images/map1/curveSmaller2.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!sideTexture1->loadFromFile("images/map1/side1.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!sideTexture2->loadFromFile("images/map1/side2.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!solidTowerTexture->loadFromFile("images/map1/solidTower.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}
	if (!solidMonsterTexture->loadFromFile("images/map1/castle.png"))
	{
		std::cout << "nie wczytalo textury MenuScene" << std::endl;
	}



	std::fstream file;

		for (int i = 0; i < 20; i++) {
			for (int k = 0; k < 20; k++) {
				tileArray[i][k].setTexture(solidTowerTexture);
				tileArray[i][k].setPosition(sf::Vector2f((widthMap / 20.0)/2+(widthMap/20.0)*k, (heightMap / 20.0)/2+(heightMap / 20.0) * i));
				
		}
		}


	std::vector<sf::Vector2i> pathPoints;

	std::fstream file2;
	file2.open("images/map1/path.txt");

	int row, column;
	sf::Vector2i c;
	if (file2.is_open()) {
		while(!file2.eof()){
			file2 >> row >> column;
			c.x = row;
			c.y = column;
	
			pathPoints.push_back(c);
	}

		file2.close();
	}


	for (int i = 1; i < pathPoints.size();i++) {
		//left or right
		if (pathPoints[i].x == pathPoints[i - 1].x) {
			//right
			if (pathPoints[i].y > pathPoints[i - 1].y) {

				for (int k = pathPoints[i].y-1; k > pathPoints[i - 1].y;k--) {

					tileArray[pathPoints[i].x][k].setTexture(sideTexture1);
					tileArray[pathPoints[i].x][k].setAvailable(false);

					tileArray[pathPoints[i].x - 1][k].setTexture(sideTexture1);
					tileArray[pathPoints[i].x - 1][k].setRotation(180);
					tileArray[pathPoints[i].x - 1][k].setAvailable(false);
				}

				if (i > 1) {
					//from top
					if (pathPoints[i - 1].x > pathPoints[i - 2].x) {

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(curveSmallerTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(curveBiggerTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

					}
					//from bottom
					else {
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(curveSmallerTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(curveBiggerTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

					}

				}
	
			}
			//left
			else {
				for (int k = pathPoints[i].y; k < pathPoints[i - 1].y-1; k++) {
					tileArray[pathPoints[i].x][k].setTexture(sideTexture1); 
					tileArray[pathPoints[i].x][k].setAvailable(false);

					tileArray[pathPoints[i].x - 1][k].setTexture(sideTexture1);
					tileArray[pathPoints[i].x - 1][k].setRotation(180);
					tileArray[pathPoints[i].x - 1][k].setAvailable(false);
				}
				
				if (i > 1) {
					//from top
					if (pathPoints[i - 1].x > pathPoints[i - 2].x) {

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(curveSmallerTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setRotation(0);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(curveBiggerTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

					}
					//from bottom
					else {
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(curveSmallerTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(curveBiggerTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);
					}

				}


			}


		}
		//up or down
		else {
			//down
			if (pathPoints[i].x > pathPoints[i - 1].x) {

				for (int k = pathPoints[i].x-1; k > pathPoints[i - 1].x; k--) {
					tileArray[k][pathPoints[i].y].setTexture(sideTexture2);
					tileArray[k][pathPoints[i].y].setRotation(180);
					tileArray[k][pathPoints[i].y].setAvailable(false);
				
					tileArray[k][pathPoints[i].y - 1].setTexture(sideTexture2);
					tileArray[k][pathPoints[i].y - 1].setAvailable(false);

				}

				if (i > 1) {
				//from left
					if (pathPoints[i - 1].y > pathPoints[i - 2].y) {

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(curveSmallerTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x-1][pathPoints[i - 1].y].setTexture(curveBiggerTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

					}
					//from right
					else {
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(curveSmallerTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(curveBiggerTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);
					}
				
				}

			}
			//up
			else {
				for (int k = pathPoints[i].x; k < pathPoints[i - 1].x-1; k++) {
					tileArray[k][pathPoints[i].y].setTexture(sideTexture2);
					tileArray[k][pathPoints[i].y].setRotation(180);
					tileArray[k][pathPoints[i].y].setAvailable(false);

					tileArray[k][pathPoints[i].y - 1].setTexture(sideTexture2);
					tileArray[k][pathPoints[i].y - 1].setAvailable(false);

				}
				if (i > 1) {
					//from left
					if (pathPoints[i - 1].y > pathPoints[i - 2].y) {

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(curveSmallerTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setRotation(0);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(curveBiggerTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

					}
					//from right
					else {
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setTexture(curveSmallerTexture1);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setRotation(180);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setTexture(sideTexture1);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y].setAvailable(false);

						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setTexture(sideTexture2);
						tileArray[pathPoints[i - 1].x - 1][pathPoints[i - 1].y - 1].setAvailable(false);

						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setTexture(curveBiggerTexture2);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setRotation(180);
						tileArray[pathPoints[i - 1].x][pathPoints[i - 1].y - 1].setAvailable(false);
					}

				}


			}
		
		}




	}

	

	for (int k = 0; k < pathPoints.size(); k++) {
		//mapPathPoints.push_back(sf::Vector2f((widthMap / 20.0) / 2 + (widthMap / 20.0) * pathPoints[k].x, (heightMap / 20.0) / 2 + (heightMap / 20.0) * pathPoints[k].y));
		mapPathPoints.push_back(sf::Vector2f( (heightMap / 20.0) * pathPoints[k].y, (widthMap / 20.0) * pathPoints[k].x));

	}


	//scaleMap();
}


void GameMap::draw(sf::RenderWindow& window) {

	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			tileArray[k][i].draw(window);
		}
	}

}


sf::Vector2f GameMap::getCenterOfTile(sf::Vector2f mMousePosition) {
	
	sf::Vector2f position(mMousePosition); 
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			if (tileArray[i][k].isColliding(mMousePosition)) {
				position = tileArray[i][k].getPosition();
			}
		}
	}
	return position;
}


bool GameMap::isTileAvailable(sf::Vector2f mMousePosition) {
	
	bool isAvailable = false;

	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			if (tileArray[i][k].isColliding(mMousePosition)) {
				if (tileArray[i][k].isTileAvailable()) {
					isAvailable = true;
				}


			}
		}
	}
	return isAvailable;

}

void GameMap::setTileType(sf::Vector2f mMousePosition, bool mType) {


	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			if (tileArray[i][k].isColliding(mMousePosition)) {
				tileArray[i][k].setAvailable(mType);
			}
		}
	}


}


std::vector<sf::Vector2f> GameMap::getPathPoints() {
	return mapPathPoints;
}