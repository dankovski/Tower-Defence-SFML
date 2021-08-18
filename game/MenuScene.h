#pragma once
#include "sfml/Graphics.hpp"
#include "Button.h"
#include "Scene.h"


#define NUMBER_OF_BUTTONS 3

class MenuScene :public Scene {
public:
	MenuScene(float mWidth, float mHeight);
	~MenuScene();
	void draw(sf::RenderWindow& mWindow);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void render(sf::RenderWindow& mWindow);
	int run(sf::RenderWindow& mWindow);
	void mouseCheck(sf::RenderWindow& mWindow);

private:
	sf::Vector2f gameSize;
	int buttonsSize;
	int selectedItemIndex;
	bool running;
	sf::Font font;
	Button* buttons[NUMBER_OF_BUTTONS];
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
};


