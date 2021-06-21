#pragma once
#include "sfml/Graphics.hpp"
#include "scene.h"
#include "button.h"
#include "player.h"

//#define numberOfButtons 1

class highscore :public scene
{
public:
	//highscore();
	highscore(int width, int height);
	int run(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void loadPlayers(sf::RenderWindow& window);

private:
	int buttonSize;
	sf::Font fontBack;
	sf::Font fontScore;
	button* buttonBack;
	std::vector<sf::Text> texts;
	int numberOfPlayers;
	bool running;
	sf::Texture texture;
	sf::Sprite sprite;

};

