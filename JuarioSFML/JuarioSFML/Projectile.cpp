#include "pch.h"
#include "Projectile.h"


Projectile::Projectile()
{
	setSize(sf::Vector2f(10, 7));
	setPosition(0, 0);
	setActive(false);

	tex.loadFromFile("../gfx/bullet.png");
	setTexture(&tex);
	gravity = 2.0f*scale;
}


Projectile::~Projectile()
{
}

void Projectile::update(float deltaTime)
{
	velocity.x = scale * direction;

	move(velocity);
}

void Projectile::collisionResponse(Sprite* sp)
{
	setActive(false);
}

void Projectile::setActive(bool a)
{
	active = a;
}


bool Projectile::getActive()
{
	return active;
}
