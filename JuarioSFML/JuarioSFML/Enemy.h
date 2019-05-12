#pragma once
#include "AnimatedSprite.h"
#include"Player.h"

class Enemy :
	public AnimatedSprite
{
public:
	Enemy();
	~Enemy();

	void update(float deltaTime);
	void collisionResponse(Player* sp);


	Input* input;
	float scale;
	int width = getSize().x;
	int height = getSize().y;

	sf::Texture texture;
	int lvl[4];

	int direction = 1;

	sf::Vector2f new_pos;
	sf::Vector2f position;

};

