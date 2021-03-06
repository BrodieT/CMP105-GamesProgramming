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
#include "Projectile.h"

class Game {
public:
	Game(sf::RenderWindow* hwnd, Input* in, int w, int h);
	~Game();

	//game loop
	void handleInput(float deltaTime, Input input);
	void update(float deltaTime);
	void render();
	
	//render functions
	void beginDraw();
	void endDraw();

	bool getPos();

	void CheckPlayerCollisionsWithWorld(Player* p);

	void fireBullet();

	GameState getState();
	
	sf::Vector2f Interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor);
	
	void setScreenWidth(int x);
	void setScreenHeight(int y);

	bool checkCollision(Sprite* s1, Sprite* s2);
	void CheckCollisionsWithWorld(Sprite* e);

	void MoveCam(bool up);
	void MoveRooms();



	void updateUI();
private:

	bool movingCam = false;


	//render window pointer and input class
	sf::RenderWindow* window;
	Input* input;

	std::vector<Enemy> enemies;
	Enemy enemyTemplate;

	//Viewport object (camera)
	sf::View player_view;

	//Target position for the viewport(camera), used to interpolate the camera position
	sf::Vector2f targetCam;
	
	//Background texture and object for base of the level
	sf::RectangleShape baseBackObj;
	sf::Texture baseBackTex;

	//Background texture and object for rest of the level
	sf::RectangleShape skyBackObj;
	sf::Texture skyBackTex;

	//Room Textures and Objects
	sf::RectangleShape roomBackObj;
	sf::Texture roomBackTex;
	
	//Tilemap for the base of the building
	Map buildingBase;
	//Tilemap for a building chunk that starts with the opening on the left
	Map buildingChunkL;
	//Tilemap for a building chunk that starts with the opening on the right
	Map buildingChunkR;
	//Tilemap for the ground outside the building
	Map ground;

	//Variabes for storing the screen width and height
	int screenWidth = 0;
	int screenHeight = 0;

	int roomHeight = 0;
	int roomWidth = 0;

	sf::Texture roomTex1;
	sf::Texture roomTex2;
	sf::Texture roomTex3;

	std::vector<sf::Texture> roomTex;
	std::vector<sf::RectangleShape> rooms;

	sf::RectangleShape room1;
	sf::RectangleShape room2;
	sf::RectangleShape room3;

	float buildingPosX;

	//The player object
	Player player;

	//UI
	sf::Font myFont;
	sf::Text AmmoCounter;
	sf::Text Health;
	sf::RectangleShape HealthBar;
	sf::RectangleShape AmmoBar;
	sf::RectangleShape HealthBarBack;
	sf::RectangleShape AmmoBarBack;
	sf::RectangleShape UIBack1;
	sf::RectangleShape UIBack2;
	sf::Text Timer;

	

	//Tracks the current gamestate
	GameState state;
};