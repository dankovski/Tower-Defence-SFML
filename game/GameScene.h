#pragma once
#include "sfml/Graphics.hpp"
#include "Scene.h"
#include "Button.h"
#include "Player.h"
#include "GameMap.h"
#include "GameHUD.h"
#include <memory>
#include "Enemy.h"
#include "Tower.h"
#include "Stage.h"
#include "RocketTower.h"
#include "GravesTower.h"
#include "TripleTower.h"
#include "StunTower.h"
#include <chrono>

class GameScene :public Scene
{
public:
	GameScene(int mWidth, int mHeight);

private:
	int run(sf::RenderWindow& mWindow);
	void render(sf::RenderWindow& mWindow, double mDeltaTime);
	void draw(sf::RenderWindow& mWindow);

	std::unique_ptr<GameMap> map;
	std::unique_ptr<GameHUD> gameHUD;
	std::unique_ptr<Player> player;

	bool running;
	bool stageStarted;
	sf::Font font;
	enum gameStates { GAME, GAME_OVER, EXIT, END_LEVEL };
	gameStates gameState;
	int gameSpeed;
	sf::Vector2f gameSize;
	sf::Text fpsText;
	sf::Text scoreText;
	sf::Text hpText;
	sf::Text gameSpeedText;
	sf::Text goldText;
	double timeFromFpsUpdate;
	int level;

	sf::Sprite gameMenuSprite;
	sf::Text gameMenuText1;
	sf::Text gameMenuText2;
	Button gameMenuButtonLeft;
	Button gameMenuButtonRight;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Tower>> towers;
	std::vector<std::shared_ptr<sf::Texture>> turretsTexturesVector;
	std::vector<std::unique_ptr<sf::Texture>> bulletsTexturesVector;
	std::vector<std::unique_ptr<sf::Texture>> enemiesTexturesVector;
	std::vector<Stage> stages;
	std::vector<Button> buttons;

};