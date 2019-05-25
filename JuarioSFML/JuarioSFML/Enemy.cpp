#include "pch.h"
#include "Enemy.h"




Enemy::Enemy()
{

	scale = 100.f;
	
	texture.loadFromFile("../gfx/dump.png");
	setTexture(&texture);
	setSize(sf::Vector2f(32, 32));
	setVelocity(30, 0);
}

void Enemy::update(float deltaTime)
{



	//AnimatedSprite::update(deltaTime);

	move(scale*deltaTime*direction, 0);





	updateAABB();
}

Enemy::~Enemy()
{
}


void Enemy::collisionResponse(Sprite* sp)
{

	//std::printf("Enemy Collision Response /n");

}


