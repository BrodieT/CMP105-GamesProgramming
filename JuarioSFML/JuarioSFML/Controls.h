#pragma once
#include "SFML/Graphics.hpp"
#include "States.h"
#include "Input.h"

class Controls
{
public:
	Controls(sf::RenderWindow* hwnd, Input* in);
	~Controls();

	//game loop
	void handleInput(float deltaTime);
	void update(float deltaTime);
	void render();

	GameState getState();

private:

	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	sf::RectangleShape background;
	sf::Texture controls;

	//render functions
	void beginDraw();
	void endDraw();

	GameState state;
};

