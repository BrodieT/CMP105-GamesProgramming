#include "pch.h"
#include "Controls.h"



Controls::Controls(sf::RenderWindow* hwnd, Input* in)
{

	//store pointer to window and input class
	window = hwnd;
	input = in;
	controls.loadFromFile("../gfx/CONTROLS.png");

	background.setTexture(&controls);
	background.setSize(sf::Vector2f(1300, 900));
	background.setPosition(0, 0);

	state = GameState::CONTROLS;
}


Controls::~Controls()
{
}


void Controls::update(float deltaTime)
{

}

void Controls::handleInput(float deltaTime)
{

}

void Controls::render()
{

	beginDraw();
	window->draw(background);
	endDraw();

}

void Controls::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Controls::endDraw()
{
	window->display();
}

GameState Controls::getState()
{
	return state;
}
