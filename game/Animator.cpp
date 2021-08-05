#include "Animator.h"

Animator::Animator(sf::Sprite* mTargetSprite, int mNumberOfFrames, float mDuration)
{
	targetSprite = mTargetSprite;
	startFrame = 0;
	endFrame = mNumberOfFrames - 1;
	duration = mDuration;
	timeFromStart = 0.0;
	currentFrame = 0;
	textureSize = mTargetSprite->getTexture()->getSize();
	targetSprite->setTextureRect(sf::IntRect(0, 0, textureSize.x/(endFrame+1), textureSize.y));
	isStarted = true;
	isLooped = false;
}

void Animator::update(double mDeltaTime)
{
	if (isStarted) {

		timeFromStart += mDeltaTime;
		if (currentFrame == endFrame) {
		}

		if (timeFromStart >= (currentFrame + 1) * duration / (endFrame + 1 - startFrame)) {
			currentFrame++;
			if (currentFrame == endFrame + 1) {

				currentFrame = 0;
				timeFromStart = 0.0;
				targetSprite->setTextureRect(sf::IntRect(0, 0, textureSize.x / (endFrame + 1), textureSize.y));
				if (isLooped) {
					isStarted = false;
				}

			}
			else {
				targetSprite->setTextureRect(sf::IntRect(currentFrame * textureSize.x / (endFrame + 1), 0, textureSize.x / (endFrame + 1), textureSize.y));
			}
		}


	}





}

void Animator::startAnimation()
{
	isStarted = true;
}

