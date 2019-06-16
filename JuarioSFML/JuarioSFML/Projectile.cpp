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

