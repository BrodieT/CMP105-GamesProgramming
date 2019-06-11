#include "pch.h"
#include "Animation.h"
Animation::Animation()
{
	currentFrame = 0;
}
Animation::~Animation()
{}
void Animation::init(int left, int top, int width, int height, int numFrames, float speed)
{
	frame.left = left;
	frame.top = top;
	frame.width = width;
	frame.height = height;
	numberOfFrames = numFrames;
	animationSpeed = speed;
}

sf::IntRect Animation::getCurrentFrame(int direction)
{
	sf::IntRect temp;
	if (direction == 1)
	{
		temp = sf::IntRect(frame.width * currentFrame, frame.top, frame.width, frame.height);
	}
	else
	{
		temp = sf::IntRect(frame.width * currentFrame + frame.width, frame.top, -frame.width, frame.height);
	}

	return temp;
}

void Animation::nextFrame()
{
	currentFrame++;
	if (currentFrame >= numberOfFrames)
	{
		currentFrame = 0;
	}
}