#include "pch.h"
#include "Menu.h"



Menu::Menu(sf::RenderWindow* hwnd, Input* in)
{

	//store pointer to window and input class
	window = hwnd;
	input = in;

	menu.loadFromFile("../gfx/MENU.png");

	background.setTexture(&menu);
	background.setSize(sf::Vector2f(1300, 900));
	background.setPosition(0, 0);
	state = GameState::MENU;
}


Menu::~Menu()
{
}


void Menu::update(float deltaTime)
{

}

void Menu::handleInput(float deltaTime)
{
}

void Menu::render()
{

	beginDraw();
	window->draw(background);
	endDraw();

}

void Menu::beginDraw()
{
	window->clear(sf::Color::Cyan);
}

void Menu::endDraw()
{
	window->display();
}

GameState Menu::getState()
{
	return state;
}