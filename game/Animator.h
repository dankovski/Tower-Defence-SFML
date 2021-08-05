#include "sfml/Graphics.hpp"
#include <iostream>

class Animator
{
public:
	Animator() {};
	Animator(sf::Sprite* mTargetSprite, int mNumberOfFrames, float mDuration, bool mIsLooped);
	void update(double mDeltaTime);
	void startAnimation();

private:
	unsigned int startFrame;
	unsigned int endFrame;
	unsigned int currentFrame;
	double timeFromStart;
	float duration;
	sf::Sprite* targetSprite;
	sf::Vector2u textureSize;
	bool isStarted;
	bool isLooped;
};
