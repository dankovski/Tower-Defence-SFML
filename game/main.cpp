#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

#include "Scene.h"
#include "MenuScene.h"
#include "SettingsScene.h"
#include "GameScene.h"
#include "Settings.h"

#define WIDTH 1200
#define HEIGHT 1000


int main() {
	
	std::unique_ptr<Settings> settings;
	settings = std::make_unique<Settings>();

	sf::RenderWindow window(sf::VideoMode(settings->getResolution().x, settings->getResolution().y), "danko granko", settings->getStyle(), settings->getContextSettings());
    window.setView(sf::View(sf::FloatRect(0,0, WIDTH, HEIGHT)));
	window.setFramerateLimit(settings->getLimitFPS());
	window.setVerticalSyncEnabled(settings->getVerticalSync());

	std::vector<std::unique_ptr<Scene>> scenes;

	scenes.push_back(std::make_unique<MenuScene>(WIDTH, HEIGHT));
	scenes.push_back(std::make_unique<SettingsScene>(WIDTH, HEIGHT, settings.get()));
	scenes.push_back(std::make_unique<GameScene>(WIDTH, HEIGHT));

	int screen = 0;
	while (screen >= 0) {
		screen = scenes[screen]->run(window);
	}
	return 0;
}