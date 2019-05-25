#pragma once
#include "AnimatedSprite.h"
#include "Input.h"
#include "Animation.h"

class Player : public AnimatedSprite
{

public:
	Player();
	~Player();
	void update(float deltaTime);
	void collisionResponse(Sprite* sp, int wall);
	void LoseLife(int lives);
	void UpdateLife(int lives);


	int buildingW = 0;
	sf::Vector2f buildingPos;

	Input* input;
	float scale;
	float gravity;
	bool falling;
	int width = getSize().x;
	int height = getSize().y;
	int lives = 3;

	sf::RectangleShape life;

	sf::Texture Life3;
	sf::Texture Life2;
	sf::Texture Life1;


protected:
	Animation walkR;
	Animation jump;
	Animation walkL;
	Animation* currentAnimation;

};

