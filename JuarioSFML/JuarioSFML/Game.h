#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Input.h"
#include <string.h>
#include "Map.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Enemy.h"
#include"States.h"
#include "Menu.h"
#include "Animation.h"


class Game {
public:
	Game(sf::RenderWindow* hwnd, Input* in);
	~Game();

	//game loop
	void handleInput(float deltaTime, Input input);
	void update(float deltaTime);
	void render();
	bool getPos();
	GameState getState();


private:

	bool checkCollision(Sprite* s1, Sprite* s2);

	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	//render functions
	void beginDraw();
	void endDraw();

	sf::RectangleShape background;
	sf::Texture BackTexture;

	//Game Variables
	Map level;
	Player player;
	sf::Texture texture2;
	Enemy enemy[4];
	GameState state;



	bool hasStarted;
};