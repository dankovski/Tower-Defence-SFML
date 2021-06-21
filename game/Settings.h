#pragma once
#include "sfml/Graphics.hpp"


class Settings
{
public:
	Settings();
	void save();
	sf::ContextSettings getContextSettings();
	sf::Vector2i getResolution();
	int getLimitFPS();
	bool getVerticalSync();
	int getStyle();
	void setSettings(int width, int height, bool fullscreen, bool vsync, int antialiasingLvl, int fpsLimit);
	bool isFullscreen();
private:
	sf::ContextSettings contextSettings;
	bool fullscreen;
	bool vsync;
	int limitFPS;
	sf::Vector2i resolution;

};

