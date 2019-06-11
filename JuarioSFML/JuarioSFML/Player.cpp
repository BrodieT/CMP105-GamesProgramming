#include "pch.h"
#include "Player.h"



Player::Player()
{

	scale = 200.f;
	gravity = 8.0f*scale;
	falling = true;
	direction = 1;
	setSize(sf::Vector2f(48, 48));
	setTexture(&playerTex);

	setVelocity(0, 10);

	playerTex.loadFromFile("../gfx/Juario3.png");

	walk.init(0, 0, 32, 32, 2, 0.3f);
	jump.init(32, 32, 32, 32, 2, 0.2f);
	idle.init(0, 32, 32, 32, 1, 0.2f);


	currentAnimation = &jump;
	frame = currentAnimation->getCurrentFrame(direction);
	setTextureRect(frame);


	updateAABB();
}

void Player::update(float deltaTime)
{



	AnimatedSprite::update(deltaTime);

	


	//jump
	if (input->isKeyDown(sf::Keyboard::W) && falling == false)
	{
		if (getPosition().x > buildingPos.x - (((buildingW / 2) - 1) * 32) && getPosition().x < buildingPos.x - (((buildingW / 2) - 3) * 32))
		{
			velocity.y = -5.f*scale;
			falling = true;
		}
		else if (getPosition().x > buildingPos.x + (((buildingW / 2) - 3) * 32) && getPosition().x < buildingPos.x + (((buildingW / 2)) * 32))
		{

			velocity.y = -5.f*scale;
			falling = true;
		}
		else
		{
			velocity.y = -3.f*scale;
			falling = true;
		}
	}



	if (input->isKeyDown(sf::Keyboard::D))
	{
		move((150 * deltaTime), 0);
		isMoving = true;
		direction = 1;
	}
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		move((-150 * deltaTime), 0);
		isMoving = true;
		direction = -1;
	}
	else
	{
		isMoving = false;
	}


	//gravity
	if (falling)
	{
		velocity.y += (gravity)*deltaTime;
		move(velocity*deltaTime);
	}


	updateAABB(); // update AABB

	elapsedTime += deltaTime;

	if (falling)
	{
		currentAnimation = &jump;
		//std::printf("Jump");
	}
	else if (isMoving)
	{

		currentAnimation = &walk;
		//std::printf("Walk");
	}
	else
	{
		currentAnimation = &idle;
		//std::printf("Idle");
	}
	


	if (elapsedTime >= currentAnimation->getAnimationTime())
	{
		//next frame
		currentAnimation->nextFrame();

		if (currentAnimation == &jump)
		{
			currentAnimation->setFrame(1);
		}

		setTextureRect(currentAnimation->getCurrentFrame(direction));
		elapsedTime = 0;
	}



}

Player::~Player()
{
}

void Player::collisionResponse(Sprite* sp, int wall)
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
				setPosition(sp->getPosition().x - getSize().x - 1, getPosition().y);
				velocity.x = -10;
				velocity.y = 10;// getVelocity().y;
			}
			if (collide.x > 5)
			{
				//left side
				falling = true;
				setPosition(sp->getPosition().x + sp->getSize().x + 1, getPosition().y);
				velocity.x = 10;
				velocity.y = 10;// getVelocity().y;

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
			setPosition(sp->getPosition().x - getSize().x - 1, getPosition().y);
			velocity.x = -10;
			velocity.y = 10;// getVelocity().y;
		}
		if (collide.x > 5)
		{
			//left side
			falling = true;
			setPosition(sp->getPosition().x + sp->getSize().x + 1, getPosition().y);
			velocity.x = 10;
			velocity.y = 10;// getVelocity().y;

		}
	}

}

void Player::enemyCollisionResponse(Sprite* e)
{
	sf::Vector2f force((getPosition().x +getSize().x/2) - (e->getPosition().x + e->getSize().x/2), -5);
	velocity = force * (scale / 5);
	falling = true;
}