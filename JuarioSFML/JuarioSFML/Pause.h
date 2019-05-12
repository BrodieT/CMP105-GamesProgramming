#pragma once
#include "SFML/Graphics.hpp"
#include "States.h"
#include "Input.h"
class Pause
{
public:
	Pause(sf::RenderWindow* hwnd, Input* in);
	~Pause();

	//game loop
	void handleInput(float deltaTime);
	void update(float deltaTime);
	void render();

	GameState getState();

private:

	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	//render functions
	void beginDraw();
	void endDraw();

	GameState state;
};

