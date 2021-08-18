#include "MenuScene.h"
#include <iostream>


MenuScene::MenuScene(float mWidth, float mHeight) {
	buttonsSize = mHeight/10;
	gameSize = sf::Vector2f(mWidth, mHeight);

	font.loadFromFile("fonts/2.ttf");
	menuTexture.loadFromFile("images/menuBackground.png");

	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(sf::Vector2f(0, 0));
	menuSprite.setScale(mWidth / (float)menuTexture.getSize().x, (float)mHeight / menuTexture.getSize().y);

	buttons[0] = new Button(&font, "Play", sf::Vector2f(mWidth / 2, mHeight / (NUMBER_OF_BUTTONS + 1) * 1), 1.5*buttonsSize, sf::Color::Red);
	buttons[1] = new Button(&font, "Options", sf::Vector2f(mWidth / 2, mHeight / (NUMBER_OF_BUTTONS + 1) * 2), buttonsSize, sf::Color::White);
	buttons[2] = new Button(&font, "Exit", sf::Vector2f(mWidth / 2, mHeight / (NUMBER_OF_BUTTONS + 1) * 3), buttonsSize, sf::Color::White);

	selectedItemIndex = 0;
	running = false;
}

MenuScene::~MenuScene()
{
}

void MenuScene::draw(sf::RenderWindow& mWindow)
{
	mWindow.draw(menuSprite);

	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		buttons[i]->draw(mWindow);
	}
}

void MenuScene::MoveUp() {

	if (selectedItemIndex - 1 >= 0)
	{
		buttons[selectedItemIndex]->setTextColor(sf::Color::White);
		buttons[selectedItemIndex]->setTextSize(buttonsSize);
		selectedItemIndex--;
	}

}

int MenuScene::GetPressedItem() {
	return selectedItemIndex;
}

void MenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < NUMBER_OF_BUTTONS)
	{
		buttons[selectedItemIndex]->setTextColor(sf::Color::White);
		buttons[selectedItemIndex]->setTextSize(buttonsSize);
		selectedItemIndex++;
	}
}

void MenuScene::mouseCheck(sf::RenderWindow& mWindow) {

	for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
		if (buttons[i]->isColliding(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y))){
			selectedItemIndex = i;
		}

	}
}

void MenuScene::render(sf::RenderWindow& mWindow) {

	mouseCheck(mWindow);
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		if (selectedItemIndex == i) {
			buttons[i]->setTextSize(buttonsSize*1.5);
			buttons[i]->setTextColor(sf::Color::Red);
		}
		else {
			buttons[i]->setTextSize(buttonsSize);
			buttons[i]->setTextColor(sf::Color::White);
		}

	}

}

int MenuScene::run(sf::RenderWindow& mWindow) {
	running = true;
	selectedItemIndex = 0;
	sf::Event event;

	while (running) {
		mWindow.clear();
		while (mWindow.pollEvent(event)) {

			if ((event.type == sf::Event::MouseButtonPressed && buttons[0]->isColliding(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x , gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y)) && event.mouseButton.button == sf::Mouse::Left) || (selectedItemIndex == 0 && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)) {
				return 2;
			}
			else if ((event.type == sf::Event::MouseButtonPressed && buttons[1]->isColliding(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y)) && event.mouseButton.button == sf::Mouse::Left) || (selectedItemIndex == 1 && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)) {
				return 1;
			}
			else if ((event.type == sf::Event::MouseButtonPressed && buttons[2]->isColliding(sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y)) && event.mouseButton.button == sf::Mouse::Left) || (selectedItemIndex == 2 && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)) {
				return -1;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				MoveUp();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				MoveDown();
			}

			if (event.type == sf::Event::Closed) {
				mWindow.close();
				return -1;
			}

		}
		
		render(mWindow);
		draw(mWindow);
		mWindow.display();
	}

	running = false;

}
