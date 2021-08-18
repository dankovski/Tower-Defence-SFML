#include "SettingsScene.h"
#include <fstream>
#include <string>

SettingsScene::SettingsScene(int mWidth, int mHeight, Settings* mSettings) {
	gameSize = sf::Vector2f(mWidth, mHeight);
	settings = mSettings;
	buttonsSize = mHeight / 20;
	running = false;
	setChoices();

	font.loadFromFile("fonts/1.ttf");
	texture.loadFromFile("images/settingsBackground.jpg");
	arrowRight.loadFromFile("images/arrowRight.png");
	arrowLeft.loadFromFile("images/arrowLeft.png");

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(mWidth / (float)texture.getSize().x, (float)mHeight / texture.getSize().y));

	sf::Text temp_text;	

	temp_text.setString("Settings");
	temp_text.setFont(font);
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize*2);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Black);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth/2, mHeight/10));
	texts.push_back(temp_text);

	temp_text.setString("Resolution");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth*0.3, mHeight * 0.25));
	texts.push_back(temp_text);
	temp_text.setString(std::to_string(res[resolutionChoice][0]) + "x" + std::to_string(res[resolutionChoice][1]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth*0.7, mHeight*0.25));
	texts.push_back(temp_text);
	buttons.push_back(Button(&arrowLeft, sf::Vector2f(mWidth * 0.55, mHeight * 0.25), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	buttons.push_back(Button(&arrowRight, sf::Vector2f(mWidth * 0.85, mHeight * 0.25), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));

	temp_text.setString("Fullscreen");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth*0.3, mHeight * 0.35));
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
	temp_text.setPosition(sf::Vector2f(mWidth * 0.7, mHeight * 0.35));
	texts.push_back(temp_text);
	buttons.push_back(Button(&arrowLeft, sf::Vector2f(mWidth * 0.55, mHeight * 0.35), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	buttons.push_back(Button(&arrowRight, sf::Vector2f(mWidth * 0.85, mHeight * 0.35), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	
	temp_text.setString("V-Sync");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth * 0.3, mHeight * 0.45));
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
	temp_text.setPosition(sf::Vector2f(mWidth * 0.7, mHeight * 0.45));
	texts.push_back(temp_text);
	buttons.push_back(Button(&arrowLeft, sf::Vector2f(mWidth * 0.55, mHeight * 0.45), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	buttons.push_back(Button(&arrowRight, sf::Vector2f(mWidth * 0.85, mHeight * 0.45), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));

	temp_text.setString("Anti-aliasing");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth * 0.3, mHeight * 0.55));
	texts.push_back(temp_text);
	temp_text.setString("x" + std::to_string(antialiasingLevels[antialiasingChoice]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth * 0.7, mHeight * 0.55));
	texts.push_back(temp_text);
	buttons.push_back(Button(&arrowLeft, sf::Vector2f(mWidth * 0.55, mHeight * 0.55), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	buttons.push_back(Button(&arrowRight, sf::Vector2f(mWidth * 0.85, mHeight * 0.55), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));

	temp_text.setString("FPS limit");
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth * 0.3, mHeight * 0.65));
	texts.push_back(temp_text);
	temp_text.setString(std::to_string(fpsLimits[fpsChoice]));
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(buttonsSize);
	temp_text.setOutlineThickness(3);
	temp_text.setOutlineColor(sf::Color::Red);
	temp_text.setOrigin(temp_text.getGlobalBounds().width / 2, temp_text.getGlobalBounds().height / 2);
	temp_text.setPosition(sf::Vector2f(mWidth * 0.7, mHeight * 0.65));
	texts.push_back(temp_text);
	buttons.push_back(Button(&arrowLeft, sf::Vector2f(mWidth * 0.55, mHeight * 0.65), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));
	buttons.push_back(Button(&arrowRight, sf::Vector2f(mWidth * 0.85, mHeight * 0.65), sf::Vector2f(mWidth * 0.05, mHeight * 0.05)));


	buttons.push_back(Button(&font, "BACK", sf::Vector2f(mWidth * 0.2, mHeight * 0.9), buttonsSize, sf::Color::White));
	buttons.push_back(Button(&font, "SAVE", sf::Vector2f(mWidth * 0.6, mHeight * 0.9), buttonsSize, sf::Color::White));
	buttons.push_back(Button(&font, "RESET", sf::Vector2f(mWidth * 0.8, mHeight * 0.9), buttonsSize, sf::Color::White));

}

void SettingsScene::render(sf::Vector2f mMousePosition) {
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

	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i].isColliding(mMousePosition)) {
			buttons[i].setTextColor(sf::Color::Red);
			buttons[i].setTextSize(1.5 * buttonsSize);
		}
		else {
			buttons[i].setTextColor(sf::Color::White);
			buttons[i].setTextSize(buttonsSize);
		}
	}



}

void SettingsScene::draw(sf::RenderWindow& mWindow) {

	mWindow.draw(sprite);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].draw(mWindow);
	}

	for (int i = 0; i < texts.size(); i++) {
		mWindow.draw(texts[i]);
	}
}

int SettingsScene::run(sf::RenderWindow& mWindow) {

	sf::Vector2f mousePosition;
	running = true;

	sf::Event event;

	while (running) {
		mousePosition = sf::Vector2f(gameSize.x * sf::Mouse::getPosition(mWindow).x / mWindow.getSize().x, gameSize.y * sf::Mouse::getPosition(mWindow).y / mWindow.getSize().y);

		while (mWindow.pollEvent(event)) {
			
			if (event.type == sf::Event::MouseButtonPressed && buttons[0].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				resolutionChoice--;
				if (resolutionChoice < 0) { resolutionChoice = 3; }

			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[1].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				resolutionChoice++;
				if (resolutionChoice > 3) { resolutionChoice = 0; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[2].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				if (fullscreen) { fullscreen = false; }
				else { fullscreen = true; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[3].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				if (fullscreen) { fullscreen = false; }
				else { fullscreen = true; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[4].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				if (vsync) { vsync = false; }
				else { vsync = true; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[5].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				if (vsync) { vsync = false; }
				else { vsync = true; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[6].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				antialiasingChoice--;
				if (antialiasingChoice < 0) { antialiasingChoice = 4; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[7].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				antialiasingChoice++;
				if (antialiasingChoice > 4) { antialiasingChoice = 0; }
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[8].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				fpsChoice--;
				if (fpsChoice < 0) {
					fpsChoice = 7;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[9].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				fpsChoice++;
				if (fpsChoice > 7) {
					fpsChoice = 0;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[10].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				setChoices();
				return 0;
			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[11].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				
				if (fullscreen) {
					if (settings->isFullscreen()) {
						mWindow.create(sf::VideoMode(res[resolutionChoice][0], res[resolutionChoice][1]), "danko granko", sf::Style::Fullscreen);
						mWindow.setView(sf::View(sf::FloatRect(0,0, 1200, 1000)));
					}
					else {
						mWindow.create(sf::VideoMode(res[resolutionChoice][0], res[resolutionChoice][1]), "danko granko", sf::Style::Fullscreen);
						mWindow.setView(sf::View(sf::FloatRect(0, 0, 1200, 1000)));
					}
				}
				else {
					if (settings->isFullscreen()) {
						mWindow.create(sf::VideoMode(res[resolutionChoice][0], res[resolutionChoice][1]), "danko granko", sf::Style::Close);
						mWindow.setView(sf::View(sf::FloatRect(0, 0, 1200, 1000)));
					}
					else {
						mWindow.setSize(sf::Vector2u(res[resolutionChoice][0], res[resolutionChoice][1]));
						mWindow.setView(sf::View(sf::FloatRect(0,0, 1200, 1000)));
					}
					mWindow.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width-res[resolutionChoice][0])/2.0, (sf::VideoMode::getDesktopMode().height - res[resolutionChoice][1]) / 2.0));
				}

				mWindow.setFramerateLimit(fpsLimits[fpsChoice]);
				mWindow.setVerticalSyncEnabled(vsync);
				settings->setSettings(res[resolutionChoice][0], res[resolutionChoice][1], fullscreen, vsync, antialiasingLevels[antialiasingChoice], fpsLimits[fpsChoice]);
				settings->save();

			}
			else if (event.type == sf::Event::MouseButtonPressed && buttons[12].isColliding(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
				setChoices();
			}
		}

		mWindow.clear();
		render(mousePosition);
		draw(mWindow);
		mWindow.display();
	}

	running = false;

}

void SettingsScene::setChoices() {

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