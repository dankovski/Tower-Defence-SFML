#include "Settings.h"
#include <fstream>
#include <iostream>

Settings::Settings()
{
	std::fstream file;

	file.open("settings.cfg");
	if (file.is_open()) {
		file >> resolution.x >> resolution.y>>fullscreen>>vsync>>contextSettings.antialiasingLevel>>limitFPS;
		file.close();
	}
	else {
		std::cout << "cant open settings.cfg"<<std::endl;
	}
	std::cout << resolution.x << std::endl << resolution.y << std::endl << fullscreen << std::endl << vsync << std::endl << contextSettings.antialiasingLevel << std::endl << limitFPS;

}

void Settings::save()
{
	std::ofstream file;
	file.open("settings.cfg", std::ios::trunc);
	if (file.is_open()) {
	file<< resolution.x << std::endl << resolution.y << std::endl << fullscreen << std::endl << vsync << std::endl << contextSettings.antialiasingLevel << std::endl << limitFPS;
	file.close();
	}
	else {
		std::cout << "cant open settings.cfg" << std::endl;
	}

}

sf::ContextSettings Settings::getContextSettings()
{
	return contextSettings;
}

sf::Vector2i Settings::getResolution()
{
	return resolution;
}

int Settings::getLimitFPS()
{
	return limitFPS;
}

bool Settings::getVerticalSync()
{
	return vsync;
}

int Settings::getStyle()
{
	if (fullscreen) {
		return 8;
	}
	else {
	return 4;
	}
	
}

void Settings::setSettings(int width, int height, bool tmpFullscreen, bool tmpVsync, int antialiasingLvl, int fpsLimit) {
	resolution.x = width;
	resolution.y = height;
	fullscreen = tmpFullscreen;
	vsync = tmpVsync;
	contextSettings.antialiasingLevel = antialiasingLvl;
	limitFPS = fpsLimit;
}

bool Settings::isFullscreen() {
	return fullscreen;
}
