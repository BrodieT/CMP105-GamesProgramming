#pragma once
#include "AnimatedSprite.h"
#include "Input.h"
#include "Animation.h"
#include "Enemy.h"

class Player : public AnimatedSprite
{

public:
	Player();
	~Player();
	void update(float deltaTime);
	void collisionResponse(Sprite* sp, int wall);
	void enemyCollisionResponse(Sprite* e);
	void LoseLife(int lives);
	void UpdateLife(int lives);

	sf::Texture playerTex;
	sf::Texture utilityTex;

	int buildingW = 0;
	sf::Vector2f buildingPos;

	Input* input;
	float scale;
	float gravity;
	bool falling;
	int width = getSize().x;
	int height = getSize().y;
	int lives = 3;

	bool isMoving = false;
	

protected:
	Animation walk;
	Animation jump;
	Animation idle;
	Animation* currentAnimation;

};

