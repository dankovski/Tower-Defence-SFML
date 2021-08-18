#include "GameScene.h"
#include <iostream>

GameScene::GameScene(int mWidth, int mHeight){
	gameSize = sf::Vector2f(mWidth, mHeight);
	running = false;
	stageStarted = false;
	level = 1;

	//loading fonts
	if (!font.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}

	//creating texts
	fpsText.setFont(font);
	fpsText.setString("FPS: 0");
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setCharacterSize(gameSize.y * 0.02);
	fpsText.setOutlineThickness(3);
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setPosition(10, 10);

	scoreText.setFont(font);
	scoreText.setString("SCORE: 0");
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setCharacterSize(gameSize.y * 0.025);
	scoreText.setOutlineThickness(3);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setPosition(gameSize.x * 0.84, 0);

	hpText.setFont(font);
	hpText.setString("HP: 100");
	hpText.setFillColor(sf::Color::Green);
	hpText.setCharacterSize(gameSize.y * 0.025);
	hpText.setOutlineThickness(3);
	hpText.setOutlineColor(sf::Color::Black);
	hpText.setPosition(gameSize.x * 0.84, gameSize.y * 0.04);

	gameSpeedText.setFont(font);
	gameSpeedText.setString("GAME SPEED: 0");
	gameSpeedText.setFillColor(sf::Color::Green);
	gameSpeedText.setCharacterSize(gameSize.y * 0.025);
	gameSpeedText.setOutlineThickness(3);
	gameSpeedText.setOutlineColor(sf::Color::Black);
	gameSpeedText.setPosition(gameSize.x * 0.84, gameSize.y * 0.08);

	goldText.setFont(font);
	goldText.setString("GOLD: 0");
	goldText.setFillColor(sf::Color::Green);
	goldText.setCharacterSize(gameSize.y * 0.025);
	goldText.setOutlineThickness(3);
	goldText.setOutlineColor(sf::Color::Black);
	goldText.setPosition(gameSize.x * 0.84, gameSize.y * 0.12);

	turretLevelText.setFont(font);
	turretLevelText.setString("LEVEL: 0");
	turretLevelText.setFillColor(sf::Color::Green);
	turretLevelText.setCharacterSize(gameSize.y * 0.025);
	turretLevelText.setOutlineThickness(3);
	turretLevelText.setOutlineColor(sf::Color::Black);
	turretLevelText.setPosition(gameSize.x * 0.84, gameSize.y * 0.48);

	turretDamageText.setFont(font);
	turretDamageText.setString("DMG: 0");
	turretDamageText.setFillColor(sf::Color::Green);
	turretDamageText.setCharacterSize(gameSize.y * 0.025);
	turretDamageText.setOutlineThickness(3);
	turretDamageText.setOutlineColor(sf::Color::Black);
	turretDamageText.setPosition(gameSize.x * 0.84, gameSize.y * 0.52);

	turretRangeText.setFont(font);
	turretRangeText.setString("RANGE: 0");
	turretRangeText.setFillColor(sf::Color::Green);
	turretRangeText.setCharacterSize(gameSize.y * 0.025);
	turretRangeText.setOutlineThickness(3);
	turretRangeText.setOutlineColor(sf::Color::Black);
	turretRangeText.setPosition(gameSize.x * 0.84, gameSize.y * 0.56);

	turretAttackSpeedText.setFont(font);
	turretAttackSpeedText.setString("Attack Speed: 0");
	turretAttackSpeedText.setFillColor(sf::Color::Green);
	turretAttackSpeedText.setCharacterSize(gameSize.y * 0.025);
	turretAttackSpeedText.setOutlineThickness(3);
	turretAttackSpeedText.setOutlineColor(sf::Color::Black);
	turretAttackSpeedText.setPosition(gameSize.x * 0.84, gameSize.y * 0.6);

	turretTimeText.setFont(font);
	turretTimeText.setString("Stun Time: 0");
	turretTimeText.setFillColor(sf::Color::Green);
	turretTimeText.setCharacterSize(gameSize.y * 0.025);
	turretTimeText.setOutlineThickness(3);
	turretTimeText.setOutlineColor(sf::Color::Black);
	turretTimeText.setPosition(gameSize.x * 0.84, gameSize.y * 0.64);

	turretPowerText.setFont(font);
	turretPowerText.setString("Slow Power: 0");
	turretPowerText.setFillColor(sf::Color::Green);
	turretPowerText.setCharacterSize(gameSize.y * 0.025);
	turretPowerText.setOutlineThickness(3);
	turretPowerText.setOutlineColor(sf::Color::Black);
	turretPowerText.setPosition(gameSize.x * 0.84, gameSize.y * 0.68);

	sellButton = Button(&font, "SELL", sf::Vector2f(gameSize.x * 0.92, gameSize.y * 0.78), gameSize.y * 0.03, sf::Color::Yellow);
	upgradeButton = Button(&font, "UPGRADE", sf::Vector2f(gameSize.x * 0.92, gameSize.y * 0.85), gameSize.y * 0.03, sf::Color::Yellow);

}

void GameScene::render(sf::RenderWindow& mWindow, double mDeltaTime) {
	sf::Vector2f mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);
	if (gameState == GAME) {
		gameHUD->render(player->getGold(), map->getCenterOfTile(mousePosition), map->isTileAvailable(mousePosition));

		//updating fps
		timeFromFpsUpdate += mDeltaTime / pow(2, gameSpeed);
		if (timeFromFpsUpdate >= 1.0) {
			fpsText.setString("FPS: " + std::to_string((int)floor(1.0 / (mDeltaTime / pow(2, gameSpeed)))));
			timeFromFpsUpdate = 0.0;
		}

		//checking defeat
		if (player->getHealth() <= 0) {
			gameState = GAME_OVER;
			gameMenuText1.setString("You Lost");
			gameMenuText2.setString("What do you want to do?");
			gameMenuText1.setOrigin(gameMenuText1.getGlobalBounds().width / 2, gameMenuText1.getGlobalBounds().height / 2);
			gameMenuText2.setOrigin(gameMenuText2.getGlobalBounds().width / 2, gameMenuText2.getGlobalBounds().height / 2);
			gameMenuButtonLeft.changeText("Play again");
			gameMenuButtonRight.changeText("Exit");
		}

		//update texts
		hpText.setString("HP: " + std::to_string(player->getHealth()));
		scoreText.setString("SCORE: " + std::to_string(player->getScore()));
		gameSpeedText.setString("GAME SPEED: " + std::to_string((int)pow(2, gameSpeed)) + "X");
		goldText.setString("GOLD: " + std::to_string(player->getGold()));

		//update buttons
		if (isAnyTowerSelected) {

			std::string temporaryText = std::to_string((float)0.8 * selectedTowerPointer->getValue());
			temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
			sellButton.changeText("SELL +"+std::to_string(selectedTowerPointer->getValue()));

			if (selectedTowerPointer->canUpgrade()) {
			temporaryText = std::to_string( (float)selectedTowerPointer->getUpgradeCost());
			temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
			upgradeButton.changeText("LVL UP -" + temporaryText);
			}
			else {
				upgradeButton.changeText("LVL MAX");
			
			}


		if (player->getGold() >= selectedTowerPointer->getUpgradeCost() && selectedTowerPointer->canUpgrade()) {
			upgradeButton.setTextColor(sf::Color::Green);
		}
		else {
			upgradeButton.setTextColor(sf::Color::Red);
		}
		}

		//render turret statistics
		if (gameHUD->isAnyTurretsClicked()) {
			std::string temporaryText;

			switch (gameHUD->getTurretClickedNumber()) {
			case 0:
				
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(GravesTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(GravesTower::getInitRange()));
				temporaryText = std::to_string(GravesTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				turretTimeText.setString("");
				turretPowerText.setString("");
				break;
			case 1:
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(RocketTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(RocketTower::getInitRange()));
				temporaryText = std::to_string(RocketTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				turretTimeText.setString("");
				turretPowerText.setString("");
				break;
			case 2:
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(StunTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(StunTower::getInitRange()));
				temporaryText = std::to_string(StunTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				temporaryText = std::to_string(StunTower::getInitStunTime());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretTimeText.setString("TIME : " + temporaryText);
				turretPowerText.setString("");
				break;
			case 3:
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(TripleTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(TripleTower::getInitRange()));
				temporaryText = std::to_string(TripleTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				turretTimeText.setString("");
				turretPowerText.setString("");
				break;
			case 4:
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(SlowTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(SlowTower::getInitRange()));
				temporaryText = std::to_string(SlowTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				temporaryText = std::to_string(SlowTower::getInitSlowTime());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretTimeText.setString("TIME: " + temporaryText);
				temporaryText = std::to_string(SlowTower::getInitSlowPower());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretPowerText.setString("POWER: " + temporaryText);
				break;
			case 5:
				turretLevelText.setString("LEVEL: 1");
				turretDamageText.setString("DMG: " + std::to_string(SuperTower::getInitDamage()));
				turretRangeText.setString("RANGE: " + std::to_string(SuperTower::getInitRange()));
				temporaryText = std::to_string(SuperTower::getInitAttackSpeed());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretAttackSpeedText.setString("AS: " + temporaryText);
				turretTimeText.setString("");
				turretPowerText.setString("");
				break;
			
			}
		
		}
		if (isAnyTowerSelected) {
			turretLevelText.setString("LEVEL: " + std::to_string(selectedTowerPointer->getLevel()));
			turretDamageText.setString("DMG: " + std::to_string(selectedTowerPointer->getDamage()));
			turretRangeText.setString("RANGE: " + std::to_string(selectedTowerPointer->getRange()));
			std::string temporaryText = std::to_string(selectedTowerPointer->getAttackSpeed());
			temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
			turretAttackSpeedText.setString("AS: " + temporaryText);
			turretTimeText.setString("");
			turretPowerText.setString("");

			if (selectedTowerPointer->getStunTime() > 0) {
				temporaryText = std::to_string(selectedTowerPointer->getStunTime());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretTimeText.setString("TIME: " + temporaryText);
			}
			else if (selectedTowerPointer->getSlowTime() > 0) {
				temporaryText = std::to_string(selectedTowerPointer->getSlowTime());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretTimeText.setString("TIME: " + temporaryText);
				temporaryText = std::to_string(selectedTowerPointer->getSlowPower());
				temporaryText = temporaryText.substr(0, temporaryText.find(".") + 3);
				turretPowerText.setString("POWER: " + temporaryText);
			}


		}

		//respawning enemies
		if (!stages.empty()) {
			if (stageStarted) {
				stages[0].render(mDeltaTime);
				if (stages[0].canMonsterSpawn(1.0)) {
					switch (stages[0].getMonsterId()) {
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
			gameState = END_LEVEL;
			if (level == 4) {
				gameMenuText1.setString("You win.");
				gameMenuText2.setString("What do you want to do?");
				gameMenuText1.setOrigin(gameMenuText1.getGlobalBounds().width / 2, gameMenuText1.getGlobalBounds().height / 2);
				gameMenuText2.setOrigin(gameMenuText2.getGlobalBounds().width / 2, gameMenuText2.getGlobalBounds().height / 2);
				gameMenuButtonLeft.changeText("Play again");
				gameMenuButtonRight.changeText("Exit game");
			}
			else {
				gameMenuText1.setString("You have beaten this level.");
				gameMenuText2.setString("What do you want to do?");
				gameMenuText1.setOrigin(gameMenuText1.getGlobalBounds().width / 2, gameMenuText1.getGlobalBounds().height / 2);
				gameMenuText2.setOrigin(gameMenuText2.getGlobalBounds().width / 2, gameMenuText2.getGlobalBounds().height / 2);
				gameMenuButtonLeft.changeText("Play again");
				gameMenuButtonRight.changeText("Next level");
			}

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
				player->addGold(enemies[i]->getRewardValue());
				player->addScore(10);
				enemies[i].reset();
				enemies.erase(enemies.begin() + i);
				i--;
			}
			else if (enemies[i]->isAttacking()) {
				stages[0].addMonsterKilled();
				player->removeHealth(enemies[i]->getDamageValue());
				enemies[i].reset();
				enemies.erase(enemies.begin() + i);


				i--;
			}
		}
	}
	else {

	if (gameMenuButtonLeft.isColliding(mousePosition)) {
		gameMenuButtonLeft.setTextColor(sf::Color::Green);
	}
	else {
		gameMenuButtonLeft.setTextColor(sf::Color::Red);
	}
	if (gameMenuButtonRight.isColliding(mousePosition)) {
		gameMenuButtonRight.setTextColor(sf::Color::Green);
	}
	else {
		gameMenuButtonRight.setTextColor(sf::Color::Red);
	}
}
	



}

void GameScene::draw(sf::RenderWindow& mWindow) {

	//draw map and hud
	map->draw(mWindow);
	gameHUD->draw(mWindow);

	//draw enemies
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw(mWindow);
	}

	//draw towers
	for (int i = 0; i < towers.size(); i++) {
		towers[i]->draw(mWindow);
	}
	for (int i = 0; i < towers.size(); i++) {
		towers[i]->drawRange(mWindow);
	}


	//draw buttons
	for (int i = 1; i < buttons.size(); i++) {
		buttons[i].draw(mWindow);
	}
	if (isAnyTowerSelected) {
		sellButton.draw(mWindow);
	upgradeButton.draw(mWindow);
	}
	if (!stageStarted) {
		buttons[0].draw(mWindow);
	}

	//draw texts
	mWindow.draw(fpsText);
	mWindow.draw(scoreText);
	mWindow.draw(hpText);
	mWindow.draw(goldText);
	mWindow.draw(gameSpeedText);
	if (gameHUD->isAnyTurretsClicked() || isAnyTowerSelected) {
		
		mWindow.draw(turretLevelText);
		mWindow.draw(turretDamageText);
		mWindow.draw(turretRangeText);
		mWindow.draw(turretAttackSpeedText);
		mWindow.draw(turretTimeText);
		mWindow.draw(turretPowerText);
	}

	//draw game menu
	if (gameState != gameStates::GAME) {
		mWindow.draw(gameMenuSprite);
		mWindow.draw(gameMenuText1);
		mWindow.draw(gameMenuText2);
		gameMenuButtonLeft.draw(mWindow);
		gameMenuButtonRight.draw(mWindow);
	}


}

int GameScene::run(sf::RenderWindow& mWindow) {

	gameState = GAME;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	double deltaTime = 0.0;
	stageStarted = false;
	bool canPlaceTurret = false;
	isAnyTowerSelected = false;
	running = true;
	sf::Event event;
	sf::Vector2f mousePosition;

	enemies.clear();
	towers.clear();
	stages.clear();
	buttons.clear();
	turretsTexturesVector.clear();
	bulletsTexturesVector.clear();

	//creating game menu
	sf::Texture gameMenuTexture;
	gameMenuTexture.loadFromFile("images/gameMenu.png");

	gameMenuSprite.setTexture(gameMenuTexture);
	gameMenuSprite.setOrigin(gameMenuSprite.getGlobalBounds().width / 2, gameMenuSprite.getGlobalBounds().height / 2);
	gameMenuSprite.setPosition(sf::Vector2f(gameSize.x * 0.5, gameSize.y * 0.5));

	gameMenuText1.setFont(font);
	gameMenuText1.setFillColor(sf::Color::Green);
	gameMenuText1.setString("Game paused.");
	gameMenuText1.setCharacterSize(gameSize.y * 0.05);
	gameMenuText1.setOutlineThickness(5);
	gameMenuText1.setOutlineColor(sf::Color::Black);
	gameMenuText1.setOrigin(gameMenuText1.getGlobalBounds().width / 2, gameMenuText1.getGlobalBounds().height / 2);
	gameMenuText1.setPosition(sf::Vector2f(gameSize.x * 0.5, gameSize.y * 0.4));

	gameMenuText2.setFont(font);
	gameMenuText2.setFillColor(sf::Color::Green);
	gameMenuText2.setString("Do you want to exit the game?");
	gameMenuText2.setCharacterSize(gameSize.y * 0.04);
	gameMenuText2.setOutlineThickness(5);
	gameMenuText2.setOutlineColor(sf::Color::Black);
	gameMenuText2.setOrigin(gameMenuText2.getGlobalBounds().width / 2, gameMenuText2.getGlobalBounds().height / 2);
	gameMenuText2.setPosition(sf::Vector2f(gameSize.x * 0.5, gameSize.y * 0.48));

	gameMenuButtonLeft = Button(&font, "YES", sf::Vector2f(gameSize.x * 0.4, gameSize.y * 0.6), gameSize.y * 0.04, sf::Color::Yellow);
	gameMenuButtonRight = Button(&font, "NO", sf::Vector2f(gameSize.x * 0.6, gameSize.y * 0.6), gameSize.y * 0.04, sf::Color::Yellow);;

	//creating game buttons
	buttons.push_back(Button(&font, "NEXT STAGE", sf::Vector2f(gameSize.x * 0.92, gameSize.y * 0.98), gameSize.y / 30.0, sf::Color::Yellow));
	buttons.push_back(Button(&font, "GAME SPEED", sf::Vector2f(gameSize.x * 0.92, gameSize.y * 0.93), gameSize.y / 30.0, sf::Color::Yellow));

	//creating stages
	switch (level) {
	case 1:
		stages.push_back(Stage(std::vector<int>{10}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 8}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5, 2}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 5, 3}, 0.5));
		break;
	case 2:
		stages.push_back(Stage(std::vector<int>{15, 8}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5, 2}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 5, 3}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 6, 4, 2}, 0.5));
		break;
	case 3:
		stages.push_back(Stage(std::vector<int>{15, 8}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5, 2}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 5, 3}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 6, 4, 2}, 0.5));
		break;
	case 4:
		stages.push_back(Stage(std::vector<int>{15, 8}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 10, 5, 2}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 5, 3}, 0.5));
		stages.push_back(Stage(std::vector<int>{15, 12, 8, 6, 4, 2}, 0.5));
		break;
	
	}



	//loading turrets textures
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[0]->loadFromFile("images/towers/tower1.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[1]->loadFromFile("images/towers/tower2.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[2]->loadFromFile("images/towers/tower3.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[3]->loadFromFile("images/towers/tower4.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[4]->loadFromFile("images/towers/tower5.png");
	turretsTexturesVector.push_back(std::make_unique<sf::Texture>());
	turretsTexturesVector[5]->loadFromFile("images/towers/tower6.png");

	//loading bullets textures
	bulletsTexturesVector.push_back(std::make_unique<sf::Texture>());
	bulletsTexturesVector[0]->loadFromFile("images/bullets/bullet1.png");
	bulletsTexturesVector.push_back(std::make_unique<sf::Texture>());
	bulletsTexturesVector[1]->loadFromFile("images/bullets/bullet2.png");

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

	//creating map, hud and player
	map = std::make_unique<GameMap>(gameSize.y, gameSize.y, level);
	gameHUD = std::make_unique<GameHUD>(sf::Vector2f(gameSize.x - gameSize.y, gameSize.y), sf::Vector2f(gameSize.y, 0), sf::Vector2f((gameSize.y) / 20.0, gameSize.y / 20.0), turretsTexturesVector);
	player = std::make_unique<Player>("Nazwa gracza", 0, 100, 1800);

	gameSpeed = 0;

	while (running) {
		mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);
		

		while (mWindow.pollEvent(event)) {
			switch (gameState) {
			case GAME:

				//starting stage (button)
				if (!stages.empty() && !stageStarted && (event.type == sf::Event::MouseButtonPressed && buttons[0].isColliding(mousePosition)) && event.mouseButton.button == sf::Mouse::Left) {
					stageStarted = true;
					stages[0].startStage();
				}

				//changing game speed (button)
				if (event.type == sf::Event::MouseButtonPressed && buttons[1].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					gameSpeed++;
					if (gameSpeed == 3) {
						gameSpeed = 0;
					}
				}

				//selling turret (button)
				if (isAnyTowerSelected && event.type == sf::Event::MouseButtonPressed && sellButton.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					player->addGold(0.8 * selectedTowerPointer->getValue());
					map->setTileType((towers[selectedTurretIndex]->getPosition()), true);
					towers[selectedTurretIndex].reset();
					towers.erase(towers.begin() + selectedTurretIndex);
					selectedTowerPointer = nullptr;
					isAnyTowerSelected = false;
				}

				//upgrading turret (button)
				if (isAnyTowerSelected && event.type == sf::Event::MouseButtonPressed && upgradeButton.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					if (player->getGold() >= selectedTowerPointer->getUpgradeCost() && selectedTowerPointer->canUpgrade()) {
						player->addGold(-selectedTowerPointer->getUpgradeCost());
						selectedTowerPointer->upgrade();
					}

				}

				//closing window
				if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
					gameState = EXIT;
					gameMenuText1.setString("Game paused.");
					gameMenuText2.setString("Do you want to exit the game?");
					gameMenuText1.setOrigin(gameMenuText1.getGlobalBounds().width / 2, gameMenuText1.getGlobalBounds().height / 2);
					gameMenuText2.setOrigin(gameMenuText2.getGlobalBounds().width / 2, gameMenuText2.getGlobalBounds().height / 2);
					gameMenuButtonLeft.changeText("No");
					gameMenuButtonRight.changeText("Yes");
				}

				//selecting turret
				for (int i = 0; i < gameHUD->getTurretsVectorSize(); i++) {
					if (!gameHUD->isAnyTurretsClicked() && event.type == sf::Event::MouseButtonPressed && gameHUD->checkTurretCollision(mousePosition, i) && event.mouseButton.button == sf::Mouse::Left) {
						gameHUD->setTurretClicked(i);
						
						if (gameHUD->isClickedTurretAvailable()) {
							isAnyTowerSelected = false;
							canPlaceTurret = false;
							for (int k = 0; k < towers.size(); k++) {
								towers[k]->setTowerSelected(false);
							}
						}
						else {
							gameHUD->setTurretsUnclicked();
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

					switch (gameHUD->getTurretClickedNumber()) {
					case 0:
						towers.push_back(std::shared_ptr<Tower>(new GravesTower(turretsTexturesVector[0].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-GravesTower::getInitValue());
						break;
					case 1:
						towers.push_back(std::shared_ptr<Tower>(new RocketTower(turretsTexturesVector[1].get(), bulletsTexturesVector[1].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-RocketTower::getInitValue());
						break;
					case 2:
						towers.push_back(std::shared_ptr<Tower>(new StunTower(turretsTexturesVector[2].get(), bulletsTexturesVector[0].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-StunTower::getInitValue());
						break;
					case 3:
						towers.push_back(std::shared_ptr<Tower>(new TripleTower(turretsTexturesVector[3].get(), bulletsTexturesVector[1].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-TripleTower::getInitValue());
						break;
					case 4:
						towers.push_back(std::shared_ptr<Tower>(new SlowTower(turretsTexturesVector[4].get(), bulletsTexturesVector[1].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-SlowTower::getInitValue());
						break;
					case 5:
						towers.push_back(std::shared_ptr<Tower>(new SuperTower(turretsTexturesVector[5].get(), bulletsTexturesVector[1].get(), map->getCenterOfTile(mousePosition))));
						player->addGold(-SuperTower::getInitValue());
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
						selectedTowerPointer = towers[i].get();
						selectedTurretIndex = i;
					}
				}

				//unselecting tower
				if (isAnyTowerSelected && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
					for (int k = 0; k < towers.size(); k++) {
						towers[k]->setTowerSelected(false);
					}
					isAnyTowerSelected = false;
					selectedTowerPointer = nullptr;
				}

				break;

			case GAME_OVER:
				if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonLeft.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					return 2;
				}
				if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonRight.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					return 0;
				}

				break;

			case EXIT:
				if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonLeft.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					gameState = GAME;
				}
				if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonRight.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
					return 0;
				}
				break;

			case END_LEVEL:
				if (level == 4) {
					if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonLeft.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
						return 2;
					}
					if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonRight.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
						return 0;
					}
				}
				else {
					if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonLeft.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
						return 2;
					}
					if (event.type == sf::Event::MouseButtonPressed && gameMenuButtonRight.isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
						level++;
						return 2;
					}
				}
				break;
			}
		}

		end = std::chrono::steady_clock::now();
		deltaTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0);
		begin = std::chrono::steady_clock::now();

		if (mWindow.hasFocus() && deltaTime <0.1 ) {
			render(mWindow, deltaTime * pow(2, gameSpeed));
		}

		mWindow.clear();
		draw(mWindow);
		mWindow.display();

	}
	running = false;

}


