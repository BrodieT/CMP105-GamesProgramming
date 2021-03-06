#pragma once
#include "AnimatedSprite.h"
#include"Player.h"

class Enemy : public AnimatedSprite
{
public:
	Enemy();
	~Enemy();

	void update(float deltaTime);
	void collisionResponse(Sprite* sp, int wall);
	void collideWithWorld(Sprite* sp, int wall);
//	bool falling = true;
	float gravity;
	float scale;
	int width = getSize().x;
	int height = getSize().y;

	sf::Texture texture;

	bool onScreen = false;
	//int direction = 1;
	float boundaryLeft = 0;
	float boundaryRight = 0;
	sf::Vector2f new_pos;
	sf::Vector2f position;

protected:
	Animation walk;
	Animation* currentAnimation;
};

