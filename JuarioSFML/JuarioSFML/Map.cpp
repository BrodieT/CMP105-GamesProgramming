#include "pch.h"
#include "Map.h"

// Constructor sets default position value.
Map::Map()
{
	position = sf::Vector2f(0, 0);
}

Map::~Map()
{
}

// Uses window pointer to render level/section. Tile by Tile.
void Map::render(sf::RenderWindow* window)
{
	for (int i = 0; i < (int)level.size(); i++)
	{
		window->draw(level[i]);
	}


}

void Map::loadTexture(const char* filename)
{
	texture.loadFromFile(filename);
}

// Stores provided TileSet
void Map::setTileSet(std::vector<Tile> ts)
{
	tileSet = ts;
}

// Stores provided TileMap
void Map::setTileMap(std::vector<int> tm, sf::Vector2u mapDimensions)
{
	tileMap = tm;
	mapSize = mapDimensions;
}

// Builds level/section, by filling a vector with Tiles in order. TileMap provides the order, TileSet provides the inidividual Tiles.
void Map::buildLevel()
{
	if (tileSet.size() > 0 && tileMap.size() > 0)
	{
		int x, y = 0;
		sf::Vector2f tileSize(tileSet[0].getSize().x, tileSet[0].getSize().y);

		for (int i = 0; i < (int)tileMap.size(); i++)
		{
			x = i % mapSize.x;
			y = (int)floor(i / mapSize.x);
			tileSet[tileMap[i]].setPosition(position.x + (x * tileSize.x), position.y + (y * tileSize.y));
			level.push_back(tileSet[tileMap[i]]);
			level[i].setTexture(&texture);
			level[i].updateAABB();
		}
	}
}