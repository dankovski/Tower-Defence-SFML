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

class GameScene :public Scene
{
public:
	GameScene(int mWidth, int mHeight);

private:
	sf::Vector2f gameSize;
	std::unique_ptr<GameMap> map;
	std::unique_ptr<GameHUD> gameHUD;
	std::unique_ptr<Player> player;
	bool running;
	int run(sf::RenderWindow& mWindow);
	void render(sf::RenderWindow& mWindow, double mDeltaTime);
	void draw(sf::RenderWindow& mWindow);
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<Tower> towers;
	std::vector<std::unique_ptr<sf::Texture>> turretsTexturesVector;
	std::vector<Stage> stages;
	bool stageStarted;
	std::vector<Button> buttons;
	sf::Font font;
};