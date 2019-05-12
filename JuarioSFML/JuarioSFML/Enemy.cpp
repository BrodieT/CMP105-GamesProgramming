#include "pch.h"
#include "Enemy.h"




Enemy::Enemy()
{

	scale = 100.f;
	lvl[0] = 750 - 32 / 2;
	lvl[1] = 558 - 32 / 2;
	lvl[2] = 366 - 32 / 2;
	lvl[3] = 174 - 32 / 2;

	texture.loadFromFile("../gfx/dump.png");
	setTexture(&texture);
	setSize(sf::Vector2f(32, 32));
	setVelocity(30, 0);
}

void Enemy::update(float deltaTime)
{



	//AnimatedSprite::update(deltaTime);




	position = getPosition();

	new_pos.x = position.x + direction * (deltaTime*scale);
	new_pos.y = getPosition().y;

	if (new_pos.x <= 256)
	{
		direction = direction * -1;
	}
	else if (new_pos.x >= 1012)
	{
		direction = direction * -1;
	}

	setPosition(new_pos);

	updateAABB();
}

Enemy::~Enemy()
{
}


void Enemy::collisionResponse(Player* sp)
{
	sp->setPosition(0, 0);
	sp->falling = true;
	sp->lives = sp->lives - 1;


}


