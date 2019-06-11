#pragma once
#include "SFML/Graphics.hpp"
#include "States.h"
#include "Input.h"

class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in);
	~Menu();

	//game loop
	void handleInput(float deltaTime);
	void update(float deltaTime);
	void render();

	GameState getState();

private:

	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	sf::Texture buttonBack;
	sf::RectangleShape playButton;
	sf::RectangleShape controlsButton;
	sf::RectangleShape exitButton;
	sf::Text playText;
	sf::Text controlsText;
	sf::Text exitText;
	sf::Text tileTxt;

	sf::Font myFont;

	sf::RectangleShape background;
	sf::Texture menu;

	//render functions
	void beginDraw();
	void endDraw();

	GameState state;
};

