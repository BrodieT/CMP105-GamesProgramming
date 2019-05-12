#include "pch.h"
#include "Game.h" 
Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	//store pointer to window and input class
	window = hwnd;
	input = in;

	state = GameState::LEVEL;

	BackTexture.loadFromFile("../gfx/Dump tower bottom1.png");

	background.setSize(sf::Vector2f(1300, 800));
	background.setTexture(&BackTexture);
	background.setPosition(0, 0);



	for (int i = 0; i < 4; i++)
	{
		enemy[i].setPosition(350, enemy[i].lvl[i]);
	}


	texture2.loadFromFile("../gfx/Juario.png");

	player.setSize(sf::Vector2f(50, 60));
	player.setTexture(&texture2);
	player.setPosition(5, 750);
	player.input = input;
	player.setVelocity(0, 10);



	level.loadTexture("../gfx/Tiles1.png");
	//level.loadTexture("../gfx/Tiles1.png");
	Tile tile;
	std::vector<Tile> tiles;
	for (int i = 0; i < 7; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setAlive(true);
		tiles.push_back(tile);
	}
	tiles[0].setAlive(false);
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tiles[5].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(34, 34, 16, 16));
	level.setTileSet(tiles);


	// Map dimensions
	sf::Vector2u mapSize(43, 26);

	// build map
	std::vector<int> map = {
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
		5, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5

	};


	level.setTileMap(map, mapSize);
	level.setPosition(sf::Vector2f(-32, -32));
	level.buildLevel();

}
Game::~Game()
{
}

bool Game::getPos()
{
	if (player.getPosition().x == 5 && player.getPosition().y == 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::update(float deltaTime)
{


	player.update(deltaTime);


	std::vector<Tile>* world = level.getLevel();
	for (int i = 0; i < (int)world->size(); i++)
	{
		// if "alive" check collision
		if ((*world)[i].isAlive())
		{
			if (checkCollision(&player, &(*world)[i]))
			{
				player.collisionResponse(&(*world)[i]);
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		enemy[i].update(deltaTime);
	}


	for (int i = 0; i < 4; i++)
	{
		if (checkCollision(&player, &enemy[i]))
		{
			enemy[i].collisionResponse(&player);
			player.falling = true;
		}
	}

	if (player.lives == 0)
	{
		player.setPosition(0, 0);
	}

}


void Game::handleInput(float deltaTime, Input input)
{
	if (input.isKeyDown(sf::Keyboard::E) && state == GameState::LEVEL && player.getPosition().x > 256 && player.getPosition().x < 320 && player.getPosition().y >32 && player.getPosition().y < 192)
	{
		input.setKeyUp(sf::Keyboard::E);

		state = GameState::BOSS;

	}
}

// check AABB
bool Game::checkCollision(Sprite* s1, Sprite* s2)
{

	//checks for collision of the right of s1 and the left of s2
	if (s1->getAABB().left + s1->getAABB().width < s2->getAABB().left)
		return false;
	//checks for collision of the left of s1 and the right of s2
	if (s1->getAABB().left > s2->getAABB().left + s2->getAABB().width)
		return false;
	//checks for collision of the bottom os s1 and the top of s2
	if (s1->getAABB().top + s1->getAABB().height < s2->getAABB().top)
		return false;
	//checks for collision of the top of s1 and the bottom of s2
	if (s1->getAABB().top > s2->getAABB().top + s2->getAABB().height)
		return false;
	return true;
}


void Game::render()
{

	beginDraw();
	window->draw(background);
	level.render(window);
	window->draw(player);

	for (int i = 0; i < 4; i++)
	{
		window->draw(enemy[i]);
	}

	window->draw(player.life);

	endDraw();

}
void Game::beginDraw()
{
	window->clear(sf::Color::Cyan);
}
void Game::endDraw()
{
	window->display();
}

GameState Game::getState()
{
	return state;
}