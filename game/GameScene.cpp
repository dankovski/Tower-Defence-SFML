#include "GameScene.h"
#include <iostream>

GameScene::GameScene(int mWidth, int mHeight){
	gameSize = sf::Vector2f(mWidth, mHeight);
	running = false;
	stageStarted = false;
}

void GameScene::render(sf::RenderWindow& mWindow, double mDeltaTime) {
	sf::Vector2f mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);

	gameHUD->render(player->getGold(), map->getCenterOfTile(mousePosition), map->isTileAvailable(mousePosition));

	//respawning enemies
	if (!stages.empty()) {
		if (stageStarted) {
			stages[0].render(mDeltaTime);
			if (stages[0].canMonsterSpawn(1.0)) {
				switch (stages[0].getMonsterId()) {
					//todo add monsters textures vector
				case 0:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[0].get(), 30, 50, 200.0, 30, map->getPathPoints(), 4, 0.4)));
					break;
				case 1:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[1].get(), 30, 100, 200.0, 30, map->getPathPoints(), 6, 0.4)));
					break;
				case 2:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[2].get(), 30, 150, 200.0, 30, map->getPathPoints(), 4, 0.4)));
					break;
				case 3:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[3].get(), 30, 200, 100.0, 30, map->getPathPoints(), 4, 0.4)));
					break;
				case 4:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[4].get(), 30, 200, 100.0, 30, map->getPathPoints(), 4, 0.6)));
					break;
				case 5:
					enemies.push_back(std::make_shared<Enemy>(Enemy(enemiesTexturesVector[5].get(), 30, 200, 100.0, 30, map->getPathPoints(), 8, 0.6)));
					break;

				}
				
			}
			if (stages[0].isStageCompleted()) {
				stageStarted = false;
				stages.erase(stages.begin());
				std::cout << "koniec stage" << std::endl;
			}
		}
	}

	//end of the level
	else {
		std::cout << "koniec poziomu" << std::endl;
	}

	//rendering enemies
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->render(mDeltaTime);
		for (int k = 0; k < towers.size(); k++) {
			towers[k]->checkBulletsCollision(enemies[i].get());
		}
	}

	//rendering towers and choosing a target for them
	for (int i = 0; i < towers.size(); i++) {
		towers[i]->render(mDeltaTime);
		if (!towers[i]->hasEnemyTarget()) {
			for (int k = 0; k < enemies.size(); k++) {
				if (towers[i]->hasEnemyInRange(enemies[k])) {
					towers[i]->setTargetEnemy(enemies[k]);
					break;
				}
			}
		}
	}

	//removing enemies
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
		towers[i]->draw(mWindow);
	}
	for (int i = 0; i < towers.size(); i++) {
		towers[i]->drawRange(mWindow);
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

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	double deltaTime = 0.0;

	bool canPlaceTurret = false;
	bool isAnyTowerSelected = false;
	running = true;
	sf::Event event;
	sf::Vector2f mousePosition;

	enemies.clear();
	towers.clear();
	stages.clear();
	buttons.clear();
	turretsTexturesVector.clear();
	bulletsTexturesVector.clear();

	stageStarted = false;

	if (!font.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}


	//creating buttons
	buttons.push_back(Button(&font, "NEXT STAGE", sf::Vector2f(gameSize.x*0.92, gameSize.y*0.92), gameSize.y/40.0, sf::Color::Yellow));

	//loading turrets textures
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[0]->loadFromFile("images/towers/tower1.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[1]->loadFromFile("images/towers/tower2.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[2]->loadFromFile("images/towers/tower3.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[3]->loadFromFile("images/towers/tower4.png");

	//loading bullets textures
	bulletsTexturesVector.push_back(std::make_unique<sf::Texture>());
	bulletsTexturesVector[0]->loadFromFile("images/bullets/bullet1.png");

	//loading enemies textures
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[0]->loadFromFile("images/enemies/enemy1.png");
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[1]->loadFromFile("images/enemies/enemy2.png");
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[2]->loadFromFile("images/enemies/enemy3.png");
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[3]->loadFromFile("images/enemies/enemy4.png");
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[4]->loadFromFile("images/enemies/enemy5.png");
	enemiesTexturesVector.push_back(std::make_unique<sf::Texture>());
	enemiesTexturesVector[5]->loadFromFile("images/enemies/enemy6.png");


	map = std::make_unique<GameMap>(gameSize.y, gameSize.y);
	gameHUD = std::make_unique<GameHUD>(sf::Vector2f(gameSize.x - gameSize.y, gameSize.y), sf::Vector2f(gameSize.y, 0), sf::Vector2f((gameSize.y)/20.0,gameSize.y /20.0), turretsTexturesVector);
	player = std::make_unique<Player>("Nazwa gracza", 0, 100, 180);



	//creating stages
	stages.push_back(Stage(std::vector<int>{1, 1, 1, 1, 1, 1}, 0.5));
	stages.push_back(Stage(std::vector<int>{5, 8, 3}, 0.5));
	stages.push_back(Stage(std::vector<int>{15, 18, 5, 1}, 0.5));


	while (running) {
		mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);


		while (mWindow.pollEvent(event)) {
			
			//starting stage (button)
			if (!stages.empty() && !stageStarted && (event.type == sf::Event::MouseButtonPressed && buttons[0].isColliding(mousePosition)) && event.mouseButton.button == sf::Mouse::Left) {
			stageStarted = true;
			stages[0].startStage();
			}

			//closing window
			if (event.type == sf::Event::Closed) {
				return 0;
			}

			//selecting turret
			for (int i = 0; i < gameHUD->getTurretsVectorSize(); i++) {
			if (!gameHUD->isAnyTurretsClicked() && event.type == sf::Event::MouseButtonPressed && gameHUD->checkTurretCollision(mousePosition, i) && event.mouseButton.button == sf::Mouse::Left) {
				gameHUD->setTurretClicked(i);
				canPlaceTurret = false;
				for (int k = 0; k < towers.size(); k++) {
					towers[k]->setTowerSelected(false);
				}
			}
			}

			//enable placing turret
			if (!canPlaceTurret && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				canPlaceTurret = true;
			}

			//unselecting turret
			if (gameHUD->isAnyTurretsClicked() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				gameHUD->setTurretsUnclicked();
			}

			//placing selected turret
			if (canPlaceTurret && gameHUD->isAnyTurretsClicked() && gameHUD->isClickedTurretAvailable() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				switch (gameHUD->getTurretClcikedNumber()) {
				case 0:
					towers.push_back(std::shared_ptr<Tower>(new GravesTower(turretsTexturesVector[gameHUD->getTurretClcikedNumber()].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
					break;
				case 1:
					towers.push_back(std::shared_ptr<Tower>(new RocketTower(turretsTexturesVector[gameHUD->getTurretClcikedNumber()].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
					break;
				case 2:
					towers.push_back(std::shared_ptr<Tower>(new StunTower(turretsTexturesVector[gameHUD->getTurretClcikedNumber()].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
					break;
				case 3:
					towers.push_back(std::shared_ptr<Tower>(new TripleTower(turretsTexturesVector[gameHUD->getTurretClcikedNumber()].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
					break;

				}
				
				canPlaceTurret = false;
				map->setTileType((mousePosition), false);
				gameHUD->setTurretsUnclicked();
			}

			//selecting tower
			for (int i = 0; i < towers.size(); i++) {
				if (event.type == sf::Event::MouseButtonPressed && towers[i]->isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left && !towers[i]->isSelected() && !gameHUD->isAnyTurretsClicked()) {
					for (int k = 0; k < towers.size(); k++) {
						towers[k]->setTowerSelected(false);
					}
					towers[i]->setTowerSelected(true);
					isAnyTowerSelected = true;
				}
			}

			//unselecting tower
			if (isAnyTowerSelected && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				for (int k = 0; k < towers.size(); k++) {
					towers[k]->setTowerSelected(false);
				}
				isAnyTowerSelected = false;
			}

		}


		end = std::chrono::steady_clock::now();
		deltaTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0);
		begin = std::chrono::steady_clock::now();

		


		if (mWindow.hasFocus() && deltaTime <0.1) {
			render(mWindow, deltaTime);
		}
		else {
			//std::cout << "dt:" << deltaTime << std::endl;
		}



		
		mWindow.clear();
		draw(mWindow);
		mWindow.display();

		
	}
	running = false;

}


