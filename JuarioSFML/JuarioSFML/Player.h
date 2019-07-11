#pragma once
#include "AnimatedSprite.h"
#include "Input.h"
#include "Animation.h"
#include "Enemy.h"
#include "Projectile.h"

class Player : public AnimatedSprite
{

public:
	Player();
	~Player();
	void update(float deltaTime);
	void collisionResponse(Sprite* sp, int wall);
	void enemyCollisionResponse(Sprite* e);
	void handleInput(float deltaTime);
	void fireBullet();

	sf::Vector2f target;

	sf::Vector2f viewCentre;
	sf::Vector2f viewSize;

	sf::Texture playerTex;
	sf::Texture utilityTex;

	std::vector<Projectile> activeBullets;
//	std::vector<Projectile> bullets;


	int buildingW = 0;
	sf::Vector2f buildingPos;

	Input* input;
	float scale;
	float gravity;
	//bool falling;
	int width = getSize().x;
	int height = getSize().y;
	int lives = 3;

	bool isMoving = false;
	bool isCrouching = false;

	int maxAmmo = 5;
	int currentAmmo = 5;

	int health = 100;

protected:
	Animation walk;
	Animation crouch;
	Animation jump;
	Animation idle;
	Animation* currentAnimation;

};

