#include "GameScene.h"
#include <iostream>

GameScene::GameScene(int mWidth, int mHeight){
	gameSize = sf::Vector2f(mWidth, mHeight);
	running = false;
	stageStarted = false;
}

void GameScene::render(sf::RenderWindow& mWindow, double mDeltaTime) {

	gameHUD->render(player->getGold(), map->getCenterOfTile(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y)), map->isTileAvailable(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y)));

	for (int i = 1; i < buttons.size(); i++) {
		buttons[i].draw(mWindow);
	}

	if (!stages.empty()) {
		if (stageStarted) {
			if (stages[0].canMonsterSpawn(1.0)) {
				enemies.push_back(std::make_shared<Enemy>(Enemy(turretsTexturesVector[stages[0].getMonsterId()].get(), 30, 30, 200.0, 30, map->getPathPoints())));
			}
			if (stages[0].isStageCompleted()) {
				stageStarted = false;
				stages.erase(stages.begin());
				std::cout << "koniec stage" << std::endl;
			}
		}
	}
	else {
		std::cout << "koniec poziomu" << std::endl;
	}


	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->render(mDeltaTime);
	}

	for (int i = 0; i < towers.size(); i++) {
		towers[i].render(mDeltaTime);
		if (!towers[i].hasEnemyTarget()) {
			for (int k = 0; k < enemies.size(); k++) {
				if (towers[i].hasEnemyInRange(enemies[k]->getGlobalBounds()) && !towers[i].hasEnemyTarget()) {
					towers[i].setTargetEnemy(enemies[k]);
					break;
				}
			}

		}


	}



	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->getHp() <= 0) {
			stages[0].addMonsterKilled();
			enemies[i].reset();
			enemies.erase(enemies.begin()+i);
			
			//todo add points and gold
			i--;
		}
		else if (enemies[i]->isAttacking()) {
			stages[0].addMonsterKilled();
			enemies[i].reset();
			enemies.erase(enemies.begin()+i);
			
			//todo minus player hp
			i--;
		}
	}
	




}

void GameScene::draw(sf::RenderWindow& mWindow) {

	map->draw(mWindow);
	
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw(mWindow);
	}

	for (int i = 0; i < towers.size(); i++) {
		towers[i].draw(mWindow);
	}

	gameHUD->draw(mWindow);

	for (int i = 1; i < buttons.size(); i++) {
		buttons[i].draw(mWindow);
	}

	if (!stageStarted) {
		buttons[0].draw(mWindow);
	}


}


int GameScene::run(sf::RenderWindow& mWindow) {
	unsigned long deltaTime = 0;
	unsigned long previousTime = clock();

	enemies.clear();
	towers.clear();
	stages.clear();
	buttons.clear();

	stageStarted = false;

	if (!font.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}

	buttons.push_back(Button(&font, "NEXT STAGE", sf::Vector2f(gameSize.x*0.92, gameSize.y*0.92), gameSize.y/40.0, sf::Color::Yellow));

	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[0]->loadFromFile("images/castle.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[1]->loadFromFile("images/tower1.png");

	map = std::make_unique<GameMap>(gameSize.y, gameSize.y);
	gameHUD = std::make_unique<GameHUD>(sf::Vector2f(gameSize.x - gameSize.y, gameSize.y), sf::Vector2f(gameSize.y, 0), sf::Vector2f((gameSize.y)/20.0,gameSize.y /20.0));
	player = std::make_unique<Player>("Nazwa gracza", 0, 100, 180);


	stages.push_back(Stage(std::vector<int>{3, 4}, 0.5));
	stages.push_back(Stage(std::vector<int>{5, 8}, 0.5));


	bool isTurretClicked = false;

	running = true;

	sf::Event event;

	sf::Vector2f mousePosition;

	while (running) {
		mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);


		while (mWindow.pollEvent(event)) {


			if (!stages.empty() && !stageStarted && (event.type == sf::Event::MouseButtonPressed && buttons[0].isColliding(mousePosition)) && event.mouseButton.button == sf::Mouse::Left) {
			stageStarted = true;
			stages[0].startStage();
			}


			if (event.type == sf::Event::Closed) {
				return 0;
			}

			for (int i = 0; i < gameHUD->getTurretsVectorSize(); i++) {
			if (!gameHUD->isAnyTurretsClicked() && event.type == sf::Event::MouseButtonPressed && gameHUD->checkTurretCollision(mousePosition, i) && event.mouseButton.button == sf::Mouse::Left) {
				gameHUD->setTurretClicked(i);
				isTurretClicked = false;
			}
			}

			if (!isTurretClicked && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				isTurretClicked = true;
			}


			if (gameHUD->isAnyTurretsClicked() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				gameHUD->setTurretsUnclicked();
			}

			if (isTurretClicked && gameHUD->isAnyTurretsClicked() && gameHUD->isClickedTurretAvailable() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				towers.push_back(Tower(turretsTexturesVector[gameHUD->getTurretClcikedNumber()].get(), map->getCenterOfTile(mousePosition), 100, 100, 100));
				isTurretClicked = false;
				map->setTileType((mousePosition), false);
				gameHUD->setTurretsUnclicked();
			}


		}

		
		mWindow.clear();
		deltaTime = clock() - previousTime;
		render(mWindow, deltaTime/1000.0);
		previousTime = clock();
		draw(mWindow);
		mWindow.display();
	}
	running = false;

}


