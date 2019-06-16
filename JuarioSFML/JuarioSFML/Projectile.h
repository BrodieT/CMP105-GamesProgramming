#pragma once
#include "Sprite.h"
class Projectile : public Sprite
{

public:
	Projectile();
	~Projectile();

	void update(float deltaTime);
	void collisionResponse(Sprite* sp);
	
	sf::Vector2f dir;
	float scale = 50.0f;
	bool active = false;
};

