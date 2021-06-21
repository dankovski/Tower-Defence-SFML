#pragma once
#include "SFML/Graphics.hpp"

class Scene
{
public:
	virtual int run(sf::RenderWindow& window) = 0;

};

