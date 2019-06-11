#pragma once
#include "Sprite.h"
class Projectile : public Sprite
{

public:
	Projectile();
	~Projectile();

	void update(float deltaTime);
	void collisionResponse(Sprite* sp);
	void setActive(bool a);
	bool getActive();
	void reInit();


	float scale = 50.0f;
	float gravity = 0.0f;
	bool active = false;
	sf::Texture tex;
};

