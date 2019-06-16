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

	//int direction = 1;

	sf::Vector2f new_pos;
	sf::Vector2f position;

protected:
	Animation walk;
	Animation* currentAnimation;
};

