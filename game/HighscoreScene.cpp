#include "HighscoreScene.h"
#include <iostream>
#include <fstream>

HighscoreScene::HighscoreScene(int mWidth, int mHeight) {
	numberOfPlayers = 0;
	buttonSize = mHeight / 20;
	running = false;
	if (!fontBack.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}
	if (!fontScore.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}
	if (!texture.loadFromFile("images/menu3.png"))
	{
		std::cout << "nie wczytalo textury" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(mWidth / (float)texture.getSize().x, (float)mHeight / texture.getSize().y);
	
	buttonBack = new Button(&fontBack, "BACK", sf::Vector2f(mWidth*0.1, mHeight*0.93), buttonSize, sf::Color::White);
}

void HighscoreScene::render(sf::RenderWindow& mWindow) {
	if (buttonBack->isColliding(sf::Mouse::getPosition(mWindow))) {
		buttonBack->setTextColor(sf::Color::Red);
		//buttonBack->setTextSize(1.5* buttonSize);
	}
	else {
		buttonBack->setTextColor(sf::Color::White);
		//buttonBack->setTextSize(buttonSize);
	}
}

void HighscoreScene::draw(sf::RenderWindow& mWindow) {

	mWindow.draw(sprite);
	buttonBack->draw(mWindow);


	for (int i = 0; i < numberOfPlayers * 3; i += 3) {
		mWindow.draw(texts[i]);
		mWindow.draw(texts[i + 1]);
		mWindow.draw(texts[i + 2]);

	}

}

void HighscoreScene::loadPlayers(sf::RenderWindow& mWindow) {

	numberOfPlayers = 0;

	std::fstream plik;

	plik.open("HighscoreScene.txt", std::ios::in);

	texts.clear();

	std::string a;
	int b;

	sf::Text number;
	sf::Text name;
	sf::Text score;

	number.setFont(fontScore);
	number.setFillColor(sf::Color::Yellow);
	number.setCharacterSize(buttonSize);
	number.setOutlineThickness(3);
	number.setOutlineColor(sf::Color::Black);
	number.setOrigin(number.getGlobalBounds().width / 2, number.getGlobalBounds().height / 2);

	name.setFont(fontScore);
	name.setFillColor(sf::Color::Yellow);
	name.setCharacterSize(buttonSize);
	name.setOutlineThickness(3);
	name.setOutlineColor(sf::Color::Black);
	name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);

	score.setFont(fontScore);
	score.setFillColor(sf::Color::Yellow);
	score.setCharacterSize(buttonSize);
	score.setOutlineThickness(3);
	score.setOutlineColor(sf::Color::Black);
	score.setOrigin(score.getGlobalBounds().width / 2, score.getGlobalBounds().height / 2);



	if (plik.good() == true) {

		do {

			plik >> a >> b;
			std::cout << a << "yyy" << b << std::endl;

			number.setString(std::to_string(numberOfPlayers + 1));
			number.setPosition(mWindow.getSize().x*0.3, mWindow.getSize().y*0.15 + mWindow.getSize().y *0.08 * numberOfPlayers);

			name.setString(a);
			name.setPosition(mWindow.getSize().x * 0.4, mWindow.getSize().y * 0.15 + mWindow.getSize().y * 0.08 * numberOfPlayers);

			score.setString(std::to_string(b));
			score.setPosition(mWindow.getSize().x * 0.7, mWindow.getSize().y * 0.15 + mWindow.getSize().y * 0.08 * numberOfPlayers);

			texts.push_back(number);
			texts.push_back(name);
			texts.push_back(score);

			numberOfPlayers++;

		} while (!plik.eof());


		plik.close();
	}
	else {
		std::cout << "nie udalo sie otworzyc pliku" << std::endl;

	}
}

int HighscoreScene::run(sf::RenderWindow& mWindow) {

	loadPlayers(mWindow);

	running = true;

	sf::Event event;

	while (running) {

		while (mWindow.pollEvent(event)) {

			if ((event.type == sf::Event::MouseButtonPressed && buttonBack->isColliding(sf::Mouse::getPosition(mWindow)) && event.mouseButton.button == sf::Mouse::Left)) {

				return 0;
			}

			//todo add option to clear highscore
		}


		mWindow.clear();
		render(mWindow);
		draw(mWindow);
		mWindow.display();

	}

	running = false;

}

