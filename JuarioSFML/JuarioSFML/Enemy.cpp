#include "pch.h"
#include "Enemy.h"




Enemy::Enemy()
{

	scale = 100.f;
	direction = -1.0f;
	
	texture.loadFromFile("../gfx/Enemy/DumpPixelSuit.png");
	setTexture(&texture);
	setSize(sf::Vector2f(32, 32));
	setVelocity(10, 0);
	gravity = 8.0f*scale;
	falling = true;
	updateAABB();
	walk.init(0, 0, 32, 32, 2, 0.1f);

	setAlive(true);

	currentAnimation = &walk;
	frame = currentAnimation->getCurrentFrame(direction);
	setTextureRect(frame);
}

void Enemy::update(float deltaTime)
{

	velocity.x = (scale *direction);

	if (falling)
	{
		velocity.y += (gravity)*deltaTime;
	}
	


	move(velocity.x*deltaTime, velocity.y*deltaTime);


	updateAABB();

	elapsedTime += deltaTime;

	if (elapsedTime >= currentAnimation->getAnimationTime())
	{
		//next frame
		currentAnimation->nextFrame();
		setTextureRect(currentAnimation->getCurrentFrame(-direction));
		elapsedTime = 0;
	}
}

Enemy::~Enemy()
{
}

void Enemy::collisionResponse(Sprite* sp, int wall)
{

	sf::Vector2f collide(getPosition().x - sp->getPosition().x, getPosition().y - sp->getPosition().y);

	if (wall == 0)
	{
		if (abs(collide.x) > abs(collide.y))
		{

			if (collide.x < -5)
			{
				falling = true;

				//right side
				setPosition(getPosition().x, sp->getPosition().y - getSize().y);
				velocity.y = 0;
				//direction *= -1.0f;

			}
			if (collide.x > 5)
			{
				//left side
				setPosition(getPosition().x, sp->getPosition().y - getSize().y);
				velocity.y = 0;
				//direction *= -1.0f;
			}
		}
		else if (abs(collide.x) < abs(collide.y))
		{
			//top side
			if (collide.y < -5)
			{
				/*if (abs(collide.x) < abs(collide.y))
				{*/
				falling = false;
				//}
				setPosition(getPosition().x, sp->getPosition().y - getSize().y);
				//velocity.y = 0;

			}
			//bottom side
			if (collide.y > 5)
			{
				setPosition(getPosition().x, sp->getPosition().y + getSize().y);
				velocity.y = 0;
			}
		}

	}
	else
	{
		if (collide.x < -5)
		{
			falling = true;

			//right side
			setPosition(sp->getPosition().x - (getSize().x), getPosition().y);
			direction = -1;
		}
		if (collide.x > 5)
		{
			//left side
			falling = true;
			setPosition(sp->getPosition().x + sp->getSize().x + 1, getPosition().y);
			direction = 1;

		}
	}

}
