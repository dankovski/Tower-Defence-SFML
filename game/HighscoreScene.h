#pragma once

#include "sfml/Graphics.hpp"
#include "Scene.h"
#include "Button.h"
#include "Player.h"

//#define numberOfButtons 1

class HighscoreScene :public Scene
{
public:
	//highscore();
	HighscoreScene(int mWidth, int mHeight);
	int run(sf::RenderWindow& mWindow);

	void render(sf::RenderWindow& mWindow);
	void draw(sf::RenderWindow& mWindow);
	void loadPlayers(sf::RenderWindow& mWindow);

private:
	int buttonSize;
	sf::Font fontBack;
	sf::Font fontScore;
	Button* buttonBack;
	std::vector<sf::Text> texts;
	int numberOfPlayers;
	bool running;
	sf::Texture texture;
	sf::Sprite sprite;

};

