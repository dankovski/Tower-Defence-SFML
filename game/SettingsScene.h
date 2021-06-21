#pragma once

#include "sfml/Graphics.hpp"
#include "Scene.h"
#include "Button.h"
#include "Player.h"
#include "Settings.h"

class SettingsScene :public Scene
{

public:

	SettingsScene(int mWidth, int mHeight, Settings* mSettings);
	int run(sf::RenderWindow& mWindow);
	void render(sf::RenderWindow& mWindow);
	void draw(sf::RenderWindow& mWindow);

private:
	sf::Vector2f gameSize;
	Settings* settings;
	int choice;
	sf::Font font;
	int buttonsSize;
	bool running;
	sf::Texture arrowRight;
	sf::Texture arrowLeft;
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<sf::Text> texts;
	std::vector<Button> buttons;

	int resolutionChoice=0; 
	int res[4][2] = { {800,600},{1280,720}, {1600,900}, {1920, 1080}};
	int fpsChoice = 0;
	int fpsLimits[8] = { 30, 60, 75, 100, 120, 144, 240, 0 };
	int antialiasingChoice=0;
	int antialiasingLevels[5] = { 0, 2, 4, 8, 16};
	bool fullscreen = false;
	bool vsync = false;

	void setChoices();

};


