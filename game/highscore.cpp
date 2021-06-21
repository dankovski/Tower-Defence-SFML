#include "highscore.h"
#include "highscore.h"
#include <iostream>
#include <fstream>

highscore::highscore(int width, int height) {
	numberOfPlayers = 0;
	buttonSize = height / 20;
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
	sprite.setScale(width / (float)texture.getSize().x, (float)height / texture.getSize().y);
	
	buttonBack = new button(&fontBack, "BACK", sf::Vector2f(width*0.1, height*0.93), buttonSize, sf::Color::White);
}

void highscore::render(sf::RenderWindow& window) {
	if (buttonBack->isColliding(sf::Mouse::getPosition(window))) {
		buttonBack->setTextColor(sf::Color::Red);
		//buttonBack->setTextSize(1.5* buttonSize);
	}
	else {
		buttonBack->setTextColor(sf::Color::White);
		//buttonBack->setTextSize(buttonSize);
	}
}

void highscore::draw(sf::RenderWindow& window) {

	window.draw(sprite);
	buttonBack->draw(window);


	for (int i = 0; i < numberOfPlayers * 3; i += 3) {
		window.draw(texts[i]);
		window.draw(texts[i + 1]);
		window.draw(texts[i + 2]);

	}

}

void highscore::loadPlayers(sf::RenderWindow& window) {

	numberOfPlayers = 0;

	std::fstream plik;

	plik.open("highscore.txt", std::ios::in);

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
			number.setPosition(window.getSize().x*0.3, window.getSize().y*0.15 + window.getSize().y *0.08 * numberOfPlayers);

			name.setString(a);
			name.setPosition(window.getSize().x * 0.4, window.getSize().y * 0.15 + window.getSize().y * 0.08 * numberOfPlayers);

			score.setString(std::to_string(b));
			score.setPosition(window.getSize().x * 0.7, window.getSize().y * 0.15 + window.getSize().y * 0.08 * numberOfPlayers);

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

int highscore::run(sf::RenderWindow& window) {

	loadPlayers(window);

	running = true;

	sf::Event event;

	while (running) {

		while (window.pollEvent(event)) {

			if ((event.type == sf::Event::MouseButtonPressed && buttonBack->isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {

				return 0;
			}

			//todo add option to clear highscore
		}


		window.clear();
		render(window);
		draw(window);
		window.display();

	}

	running = false;

}

