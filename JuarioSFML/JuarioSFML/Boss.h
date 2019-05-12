#pragma once
#include "SFML/Graphics.hpp"
#include "States.h"
#include "Input.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Map.h"
#include "Player.h"



class Boss
{
public:
	Boss(sf::RenderWindow* hwnd, Input* in);
	~Boss();

	//game loop
	void handleInput(float deltaTime);
	void update(float deltaTime);
	void render();

	GameState getState();

private:

	bool checkCollision(Sprite* s1, Sprite* s2);

	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	sf::RectangleShape background;
	sf::Texture boss;

	//render functions
	void beginDraw();
	void endDraw();
	//Game Variables

	Map level;
	Player player;
	sf::Texture texture;


	GameState state;
};

