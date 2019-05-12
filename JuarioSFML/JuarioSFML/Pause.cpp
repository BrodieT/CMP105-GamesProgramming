#include "pch.h"
#include "Pause.h"



Pause::Pause(sf::RenderWindow* hwnd, Input* in)
{
	//store pointer to window and input class
	window = hwnd;
	input = in;

	state = GameState::PAUSE;
}


Pause::~Pause()
{
}

void Pause::update(float deltaTime)
{

}

void Pause::handleInput(float deltaTime)
{


}

void Pause::render()
{

	beginDraw();
	endDraw();

}

void Pause::beginDraw()
{
	window->clear(sf::Color::Cyan);
}

void Pause::endDraw()
{
	window->display();
}

GameState Pause::getState()
{
	return state;
}
