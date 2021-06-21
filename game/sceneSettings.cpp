#include "sceneSettings.h"
#include <fstream>
#include <string>

sceneSettings::sceneSettings(int width, int height, Settings* sett) {
	settings = sett;
	buttonsSize = height / 20;
	running = false;
	setChoices();

	if (!font.loadFromFile("fonts/1.ttf"))
	{
		std::cout << "nie wczytalo fontow" << std::endl;
	}

	if (!texture.loadFromFile("images/menu22.png"))
	{
		std::cout << "nie wczytalo textury" << std::endl;
	}

	if (!arrowRight.loadFromFile("images/arrowRight.png"))
	{
		std::cout << "nie wczytalo textury" << std::endl;
	}
	if (!arrowLeft.loadFromFile("images/arrowLeft.png"))
	{
		std::cout << "nie wczytalo textury" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(width / (float)texture.getSize().x, (float)height / texture.getSize().y));

	sf::Text temp_text;	

	temp_text.setString("Settings");
	temp_text.setFont(font);
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize*2);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Black);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width/2, height/10));
	texts.push_back(temp_text);

	temp_text.setString("Resolution");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width*0.3, height * 0.25));
	texts.push_back(temp_text);
	temp_text.setString(std::to_string(res[resolutionChoice][0]) + "x" + std::to_string(res[resolutionChoice][1]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width*0.7, height*0.25));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.25), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.25), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("Fullscreen");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width*0.3, height * 0.35));
	texts.push_back(temp_text);
	if (fullscreen) {
	temp_text.setString("YES");
	}
	else {
		temp_text.setString("NO");
	}
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.35));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.35), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.35), sf::Vector2f(width * 0.05, height * 0.05)));
	
	temp_text.setString("V-Sync");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.45));
	texts.push_back(temp_text);
	if (vsync) {
		temp_text.setString("ON");
	}
	else {
		temp_text.setString("OFF");
	}
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.45));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.45), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.45), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("Anti-aliasing");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.55));
	texts.push_back(temp_text);
	temp_text.setString("x" + std::to_string(antialiasingLevels[antialiasingChoice]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.55));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.55), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.55), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("FPS limit");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.65));
	texts.push_back(temp_text);
	temp_text.setString(std::to_string(fpsLimits[fpsChoice]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.65));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.65), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.65), sf::Vector2f(width * 0.05, height * 0.05)));


	buttons.push_back(button(&font, "BACK", sf::Vector2f(width * 0.2, height * 0.9), buttonsSize, sf::Color::White));

	buttons.push_back(button(&font, "SAVE", sf::Vector2f(width * 0.6, height * 0.9), buttonsSize, sf::Color::White));

	buttons.push_back(button(&font, "RESET", sf::Vector2f(width * 0.8, height * 0.9), buttonsSize, sf::Color::White));

	

}

void sceneSettings::render(sf::RenderWindow& window) {

	texts[2].setString(std::to_string(res[resolutionChoice][0])+"x"+ std::to_string(res[resolutionChoice][1]));
	if (fullscreen) {
		texts[4].setString("YES");
	}
	else {
		texts[4].setString("NO");
	}
	if (vsync) {
		texts[6].setString("ON");
	}
	else {
		texts[6].setString("OFF");
	}
	texts[8].setString("x" + std::to_string(antialiasingLevels[antialiasingChoice]));

	texts[10].setString(std::to_string(fpsLimits[fpsChoice]));

	//if (buttonBack->isColliding(sf::Mouse::getPosition(window))) {

	//	buttonBack->setTextColor(sf::Color::Red);
	//	buttonBack->setTextSize(1.5*buttonsSize);

	//}
	//else {

	//	buttonBack->setTextColor(sf::Color::White);
	//	buttonBack->setTextSize(buttonsSize);
	//}
}


void sceneSettings::draw(sf::RenderWindow& window) {

	window.draw(sprite);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].draw(window);
	}

	for (int i = 0; i < texts.size(); i++) {
		window.draw(texts[i]);
	}
}


int sceneSettings::run(sf::RenderWindow& window) {


	running = true;

	sf::Event event;

	while (running) {

		while (window.pollEvent(event)) {

			if ((event.type == sf::Event::MouseButtonPressed && buttons[0].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				resolutionChoice--;
				if (resolutionChoice < 0) { resolutionChoice = 3; }

			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[1].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				resolutionChoice++;
				if (resolutionChoice > 3) { resolutionChoice = 0; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[2].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				if (fullscreen) { fullscreen = false; }
				else { fullscreen = true; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[3].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				if (fullscreen) { fullscreen = false; }
				else { fullscreen = true; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[4].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				if (vsync) { vsync = false; }
				else { vsync = true; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[5].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				if (vsync) { vsync = false; }
				else { vsync = true; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[6].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				antialiasingChoice--;
				if (antialiasingChoice < 0) { antialiasingChoice = 4; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[7].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				antialiasingChoice++;
				if (antialiasingChoice > 4) { antialiasingChoice = 0; }
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[8].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				fpsChoice--;
				if (fpsChoice < 0) {
					fpsChoice = 7;
				}
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[9].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				fpsChoice++;
				if (fpsChoice > 7) {
					fpsChoice = 0;
				}
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[10].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				return 0;
			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[11].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				
				if (!fullscreen) {
					window.create(sf::VideoMode(res[resolutionChoice][0], res[resolutionChoice][1]), "danko granko", sf::Style::Close);
					recalculate(res[resolutionChoice][0], res[resolutionChoice][1]);
					//window.setSize(sf::Vector2u(res[resolutionChoice][0], res[resolutionChoice][1]));
					//window.setView(sf::View(sf::FloatRect(0,0, res[resolutionChoice][0], res[resolutionChoice][1])));
				}
				if (fullscreen) {
					window.create(sf::VideoMode(res[resolutionChoice][0], res[resolutionChoice][1]), "danko granko", sf::Style::Fullscreen);
					recalculate(res[resolutionChoice][0], res[resolutionChoice][1]);
					//window.setView(sf::View(sf::FloatRect(0, 0, res[resolutionChoice][0], res[resolutionChoice][1])));
				}
				window.setFramerateLimit(fpsLimits[fpsChoice]);
				window.setVerticalSyncEnabled(vsync);


				settings->setSettings(res[resolutionChoice][0], res[resolutionChoice][1], fullscreen, vsync, antialiasingLevels[antialiasingChoice], fpsLimits[fpsChoice]);
				settings->save();
				//recalculate(res[resolutionChoice][0], res[resolutionChoice][1]);


			}
			if ((event.type == sf::Event::MouseButtonPressed && buttons[12].isColliding(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)) {
				setChoices();
			}

		}


		window.clear();
		render(window);
		draw(window);
		window.display();

	}

	running = false;

}

void sceneSettings::recalculate(int width, int height) {
	buttonsSize = height / 20;
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(width / (float)texture.getSize().x, (float)height / texture.getSize().y));

	texts.clear();
	buttons.clear();

	sf::Text temp_text;

	temp_text.setString("Settings");
	temp_text.setFont(font);
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize * 2);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Black);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width / 2, height / 10));
	texts.push_back(temp_text);

	temp_text.setString("Resolution");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.25));
	texts.push_back(temp_text);
	temp_text.setString("800x600");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.25));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.25), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.25), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("Fullscreen");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.35));
	texts.push_back(temp_text);
	temp_text.setString("No");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.35));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.35), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.35), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("V-Sync");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.45));
	texts.push_back(temp_text);
	temp_text.setString("Off");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.45));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.45), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.45), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("Anti-aliasing");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.55));
	texts.push_back(temp_text);
	temp_text.setString("x4");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.55));
	texts.push_back(temp_text);
	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.55), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.55), sf::Vector2f(width * 0.05, height * 0.05)));

	temp_text.setString("FPS limit");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.3, height * 0.65));
	texts.push_back(temp_text);
	temp_text.setString("60");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(width * 0.7, height * 0.65));
	texts.push_back(temp_text);

	buttons.push_back(button(&arrowLeft, sf::Vector2f(width * 0.55, height * 0.65), sf::Vector2f(width * 0.05, height * 0.05)));
	buttons.push_back(button(&arrowRight, sf::Vector2f(width * 0.85, height * 0.65), sf::Vector2f(width * 0.05, height * 0.05)));


	buttons.push_back(button(&font, "BACK", sf::Vector2f(width * 0.2, height * 0.9), buttonsSize, sf::Color::White));

	buttons.push_back(button(&font, "SAVE", sf::Vector2f(width * 0.6, height * 0.9), buttonsSize, sf::Color::White));

	buttons.push_back(button(&font, "RESET", sf::Vector2f(width * 0.8, height * 0.9), buttonsSize, sf::Color::White));



}

void sceneSettings::setChoices() {

	if (settings->getResolution().x == 800 && settings->getResolution().y == 600)
	{
		resolutionChoice = 0;
	}
	else if (settings->getResolution().x == 1280 && settings->getResolution().y == 720)
	{
		resolutionChoice = 1;
	}
	else if (settings->getResolution().x == 1600 && settings->getResolution().y == 900)
	{
		resolutionChoice = 2;
	}
	else
	{
		resolutionChoice = 3;
	}

	if (settings->getLimitFPS()==30)
	{
		fpsChoice = 0;
	}
	else if (settings->getLimitFPS() == 60)
	{
		fpsChoice = 1;
	}
	else if (settings->getLimitFPS() == 75)
	{
		fpsChoice = 2;
	}
	else if (settings->getLimitFPS() == 100)
	{
		fpsChoice = 3;
	}
	else if (settings->getLimitFPS() == 120)
	{
		fpsChoice = 4;
	}
	else if (settings->getLimitFPS() == 144)
	{
		fpsChoice = 5;
	}
	else if (settings->getLimitFPS() == 240)
	{
		fpsChoice = 6;
	}
	else {
		fpsChoice = 7;
	}

	if (settings->getContextSettings().antialiasingLevel == 0) {
		antialiasingChoice = 0;
	}
	else if (settings->getContextSettings().antialiasingLevel == 2) {
		antialiasingChoice = 1;
	}
	else if (settings->getContextSettings().antialiasingLevel == 4) {
		antialiasingChoice = 2;
	}
	else if (settings->getContextSettings().antialiasingLevel == 8) {
		antialiasingChoice = 3;
	}
	else{
		antialiasingChoice = 4;
	}

	if (settings->getStyle() == 8) {
		fullscreen = true;
	}
	else {
		fullscreen = false;
	}

	if (settings->getVerticalSync()) {
		vsync = true;
	}
	else {
		vsync = false;
	}


}