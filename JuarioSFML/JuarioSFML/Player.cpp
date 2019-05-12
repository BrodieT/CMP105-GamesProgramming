#include "pch.h"
#include "Player.h"



Player::Player()
{

	scale = 200.f;
	gravity = 8.0f*scale;
	falling = true;

	Life1.loadFromFile("../gfx/Goomba.png");
	Life2.loadFromFile("../gfx/Mushroom.png");
	Life3.loadFromFile("../gfx/MushroomTrans.png");

	life.setSize(sf::Vector2f(100, 50));
	life.setPosition(100, 50);



	walkR.init(0, 0, 202, 325, 4, 0.3f);
	jump.init(0, 326, 200, 325, 1, 0.2f);
	walkL.init(0, 0, 202, 325, 4, 0.3f);

	currentAnimation = &walkR;
	frame = currentAnimation->getCurrentFrame();
	setTextureRect(frame);


	updateAABB();
}

void Player::update(float deltaTime)
{



	AnimatedSprite::update(deltaTime);
	//jump
	if (input->isKeyDown(sf::Keyboard::Up) && falling == false)
	{
		if (getPosition().x > 256 && getPosition().x < 320 && getPosition().y < 658 && getPosition().y > 466)
		{
			velocity.y = -4.f*scale;
			falling = true;
		}
		else if (getPosition().x > 948 && getPosition().x < 1012 && getPosition().y < 850 && getPosition().y > 658)
		{
			velocity.y = -4.f*scale;
			falling = true;
		}
		else if (getPosition().x > 948 && getPosition().x < 1012 && getPosition().y < 434 && getPosition().y > 274)
		{
			velocity.y = -4.f*scale;
			falling = true;
		}
		else
		{
			velocity.y = -3.f*scale;
			falling = true;
		}
	}



	//move right
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		move((150 * deltaTime), 0);
		currentAnimation = &walkR;
	}

	//move left
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		move((-150 * deltaTime), 0);
		currentAnimation = &walkL;
	}


	//gravity
	if (falling)
	{
		currentAnimation = &jump;
		velocity.y += (gravity)*deltaTime;
		move(velocity*deltaTime);
	}
	else
	{
		currentAnimation = &walkR;
	}

	if (getPosition().y >= 750)
	{
		setPosition(getPosition().x, 750 - getSize().y / 2);
		falling = false;
	}

	if (getPosition().x == 1120 && input->isKeyDown(sf::Keyboard::Return))
	{
		velocity.y = -2.f*scale * 2;

	}
	updateAABB(); // update AABB

	elapsedTime += deltaTime;

	if (elapsedTime >= currentAnimation->getAnimationTime())
	{
		//next frame
		currentAnimation->nextFrame();
		setTextureRect(currentAnimation->getCurrentFrame());
		elapsedTime = 0;
	}
}

Player::~Player()
{
}

void Player::collisionResponse(Sprite* sp)
{


	sf::Vector2f collide(getPosition().x - sp->getPosition().x, getPosition().y - sp->getPosition().y);

	if (abs(collide.x) > abs(collide.y))
	{

		if (collide.x < -5)
		{
			//right side
			setPosition(sp->getPosition().x - getSize().x - 1, getPosition().y);
			velocity.x = 0;
		}
		if (collide.x > 5)
		{
			//left side
			setPosition(sp->getPosition().x + sp->getSize().x + 1, getPosition().y);
			velocity.x = 0;
		}
	}
	else
	{
		//top side
		if (collide.y < -5)
		{
			falling = false;
			setPosition(getPosition().x, sp->getPosition().y - getSize().y);
			velocity.y = 0;
		}
		//bottom side
		if (collide.y > 5)
		{
			setPosition(getPosition().x, sp->getPosition().y + getSize().y);
			velocity.y = 0;
		}
	}



}

void Player::LoseLife(int lives)
{
	lives = lives - 1;
}

void Player::UpdateLife(int lives)
{
	switch (lives)
	{
	case 1: life.setTexture(&Life1); break;
	case 2: life.setTexture(&Life2); break;
	case 3: life.setTexture(&Life3); break;
	default: return;
	}
}