#include "pch.h"
#include "Projectile.h"


Projectile::Projectile()
{
	setSize(sf::Vector2f(10, 7));
	setPosition(0, 0);
	setAlive(false);
	scale = 0.01;
	setFillColor(sf::Color::Red);
	setSize(sf::Vector2f(10, 5));
}


Projectile::~Projectile()
{
}

void Projectile::update(float deltaTime)
{	
	velocity.x = scale * dir.x * -1;
	velocity.y = scale * dir.y * -1;
	move(velocity);	
}

void Projectile::collisionResponse(Sprite* sp)
{
	setAlive(false);
}

void Projectile::collisionResponse(Sprite* sp, int x)
{
	std::printf("Blep");
	setAlive(false);
}


void Projectile::CheckCollisionWithWorld(std::vector<Tile>* buildingB, std::vector<Tile>* buildingCR, std::vector<Tile>* buildingCL, std::vector<int>* buildingBInt, std::vector<int>* buildingCLInt, std::vector<int>* buildingCRInt, std::vector<Tile>* gTile)
{
	for (int i = 0; i < (int)buildingB->size(); i++)
	{
		// if "alive" check collision
		if ((*buildingB)[i].isAlive())
		{
			if (getGlobalBounds().intersects((*buildingB)[i].getGlobalBounds()))
			{
				setAlive(false);
			}
		}
	}

	//Checks for collision between the player and the Right chunk of the building 
	//and triggers the player collision response if necessary
	for (int i = 0; i < (int)buildingCR->size(); i++)
	{
		// if "alive" check collision
		if ((*buildingCR)[i].isAlive())
		{
			// if "alive" check collision
			if ((*buildingCR)[i].isAlive())
			{
				if (getGlobalBounds().intersects((*buildingCR)[i].getGlobalBounds()))
				{
					setAlive(false);
				}
			}
		}
	}

	//Checks for collision between the player and the Left chunk of the building 
	//and triggers the player collision response if necessary
	for (int i = 0; i < (int)buildingCL->size(); i++)
	{// if "alive" check collision
		if ((*buildingCL)[i].isAlive())
		{
			// if "alive" check collision
			if ((*buildingCL)[i].isAlive())
			{
				if (getGlobalBounds().intersects((*buildingCL)[i].getGlobalBounds()))
				{
					setAlive(false);
				}
			}
		}
	}

	//Checks for collision between the player and the ground outside of the building 
	//and triggers the player collision response if necessary
	for (int i = 0; i < (int)gTile->size(); i++)
	{
		// if "alive" check collision
		if ((*gTile)[i].isAlive())
		{
			if(getGlobalBounds().intersects((*gTile)[i].getGlobalBounds()))
			{
				setAlive(false);
			}
		}
	}


}

