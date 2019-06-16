#pragma once
#include "Sprite.h"
#include "Tile.h"

class Projectile : public Sprite
{

public:
	Projectile();
	~Projectile();

	void update(float deltaTime);
	void collisionResponse(Sprite* sp);
	void collisionResponse(Sprite* sp, int x);
	void CheckCollisionWithWorld(std::vector<Tile>* buildingB, std::vector<Tile>* buildingCR, std::vector<Tile>* buildingCL, std::vector<int>* buildingBInt, std::vector<int>* buildingCLInt, std::vector<int>* buildingCRInt, std::vector<Tile>* gTile);

	sf::Vector2f dir;
	float scale = 50.0f;
	bool active = false;
};

