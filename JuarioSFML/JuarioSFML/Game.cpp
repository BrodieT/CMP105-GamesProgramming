#include "pch.h"
#include "Game.h" 

using namespace std;

Game::Game(sf::RenderWindow* hwnd, Input* in, int w, int h)
{
	//store pointer to window and input class
	window = hwnd;
	input = in;

	//Store the width and height of the screen
	setScreenWidth(w);
	setScreenHeight(h);

	//Init the viewport(camera)
	player_view = sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
	player_view.setCenter(sf::Vector2f(w / 2, h / 2));
	window->setView(player_view);
	targetCam = player_view.getCenter();

	
	//Init gamestate
	state = GameState::LEVEL;

	//Setup the background texture and object for the base of the level
	baseBackTex.loadFromFile("../gfx/Dump tower bottom1.png");
	baseBackObj.setSize(sf::Vector2f(screenWidth, screenHeight));
	baseBackObj.setTexture(&baseBackTex);
	baseBackObj.setPosition(0, 0);


	//FIXME enemy init
	//for (int i = 0; i < 4; i++)
	//{
	//	enemy[i].setPosition(350, enemy[i].lvl[i]);
	//}


#pragma region InitTileMaps

	//Load in tilemap textures for all the level components
	buildingBase.loadTexture("../gfx/Tiles1.png");
	buildingChunkR.loadTexture("../gfx/Tiles1.png");
	buildingChunkL.loadTexture("../gfx/Tiles1.png");
	ground.loadTexture("../gfx/Tiles1.png");

	//Setup the tilemap
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
	
	//Set the tileset of each of the level components
	buildingBase.setTileSet(tiles);
	buildingChunkR.setTileSet(tiles);
	buildingChunkL.setTileSet(tiles);
	ground.setTileSet(tiles);


	// Calculate the map dimensions
	int mapWidth = screenWidth / 32;
	int mapHeight = screenHeight / 32;

	//Set the dimensions of the building component of the level
	int buildingWidth = 30;
	int buildingHeight = mapHeight;
	sf::Vector2u buildingSize(buildingWidth, buildingHeight);
	
	//Vectors to store the three possible map parts of the level
	std::vector<int> baseBuildMp;
	std::vector<int> buildChunkLMp;
	std::vector<int> buildChunkRMp;
#pragma endregion

#pragma region FillTileMaps
	//Vectors to store each possible row in the building map components to be added dynamically
	std::vector<int> FloorLeftOpening = { 6, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6 };
	std::vector<int> FloorRightOpening = { 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 6 };
	std::vector<int> Wall = { 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 };
	std::vector<int> Door = { 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<int> Floor = { 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

	//Tracks which floor is to be placed
	int floorTracker = 0;


	//Create the base of the building by looping through the number of rows in the map and adding the appropriate values based on the predifined building parts
	//Added to the map vector in reverse-order as it is drawn from top to bottom
	for (int i = 0; i < buildingHeight; i++)
	{
		//Add the complete floor with no gaps to the first row ( the bottom of the building)
		if (i == 0)
		{
			for (int j = 0; j < buildingWidth; j++)
			{
				baseBuildMp.insert(baseBuildMp.begin(), Floor.at(j));
			}
		}//Add the doorway pieces to the second and third row (standard wall piece with blank tiles on one side to allow passage by player
		else if (i == 1 || i == 2)
		{
			for (int j = 0; j < buildingWidth; j++)
			{
				baseBuildMp.insert(baseBuildMp.begin(), Door.at(j));
			}
		}//Every six rows in the map, add a floor piece
		else if (i % 6 == 0)
		{
			//Depending on the value of the floor tracker variable, add either a left floor or a right floor
			//This allows the floors to alternate
			if (floorTracker % 2 == 0)
			{
				for (int j = 0; j < buildingWidth; j++)
				{
					baseBuildMp.insert(baseBuildMp.begin(), FloorLeftOpening.at(j));
				}
				floorTracker++;
			}
			else if (floorTracker %2 != 0)
			{
				for (int j = 0; j < buildingWidth; j++)
				{
					baseBuildMp.insert(baseBuildMp.begin(), FloorRightOpening.at(j));
				}
				floorTracker++;
			}
		}//If none of the above conditions are met, a standard wall piece is added 
		else
		{
			for (int j = 0; j < buildingWidth; j++)
			{
				baseBuildMp.insert(baseBuildMp.begin(), Wall.at(j));
			}
		}
	}

	//reset the floor tracker for the creation of the next level chunk
	floorTracker = 0;

	//Create the level chunk by looping through each row of the map and adding the appropriate piece
	//Note: loops 1 less than the base chunk to prevent a floor piece that is 2 blocks thick
	for (int i = 1; i < buildingHeight; i++)
	{
		//Every six rows add a floor piece
		if (i % 6 == 0)
		{
			//check the floor tracker and alternate floors
			if (floorTracker % 2 == 0)
			{
				for (int j = 0; j < buildingWidth; j++)
				{
					buildChunkRMp.insert(buildChunkRMp.begin(), FloorRightOpening.at(j));
					buildChunkLMp.insert(buildChunkLMp.begin(), FloorLeftOpening.at(j));
				}
				floorTracker++;
			}
			else if (floorTracker % 2 != 0)
			{
				for (int j = 0; j < buildingWidth; j++)
				{
					buildChunkRMp.insert(buildChunkRMp.begin(), FloorLeftOpening.at(j));
					buildChunkLMp.insert(buildChunkLMp.begin(), FloorRightOpening.at(j));

				}
				floorTracker++;
			}
		}//Otherwise add a standard wall piece
		else
		{
			for (int j = 0; j < buildingWidth; j++)
			{
				buildChunkRMp.insert(buildChunkRMp.begin(), Wall.at(j));
				buildChunkLMp.insert(buildChunkLMp.begin(), Wall.at(j));
			}
		}
	}
	

	buildingBase.setTileMap(baseBuildMp, buildingSize);
	buildingBase.setPosition(sf::Vector2f(((screenWidth/2)-(buildingWidth/2)*32), (0)));
	buildingBase.buildLevel();

	buildingChunkL.setTileMap(buildChunkLMp, buildingSize);
	buildingChunkL.setPosition(sf::Vector2f(((screenWidth / 2) - (buildingWidth / 2) * 32), -(screenHeight*2)+64));
	buildingChunkL.buildLevel();

	buildingChunkR.setTileMap(buildChunkRMp, buildingSize);
	buildingChunkR.setPosition(sf::Vector2f(((screenWidth / 2) - (buildingWidth / 2) * 32), -(screenHeight)+32));
	buildingChunkR.buildLevel();

	//Create the ground map for outside the building
	sf::Vector2u GroundSize(screenWidth, 1);
	std::vector<int> GroundMap;
	 
	for (int k = 0; k < screenWidth; k++)
	{
		GroundMap.push_back(2);
	}

	ground.setTileMap(GroundMap, GroundSize);
	ground.setPosition(sf::Vector2f(0, screenHeight - 32));
	ground.buildLevel();

#pragma endregion

	//Init player character
	playerTex.loadFromFile("../gfx/Juario.png");
	player.setSize(sf::Vector2f(25, 50));
	player.setTexture(&playerTex);
	player.setPosition(5, screenHeight - 400);
	player.input = input;
	player.setVelocity(0, 10);

	//Init enemy character

	enemyTest.setSize(sf::Vector2f(25, 50));
	enemyTest.setTexture(&playerTex);
	enemyTest.setPosition(screenWidth / 2, screenHeight - 400);
	enemyTest.setVelocity(0, 10);

	player.buildingW = buildingWidth;
	player.buildingPos = sf::Vector2f(((screenWidth / 2)), (0));

}

Game::~Game()
{
}

#pragma region GameLoop
void Game::handleInput(float deltaTime, Input input)
{
	//FIXME Transition into the boss fight level
	/*if (input.isKeyDown(sf::Keyboard::E) && state == GameState::LEVEL && player.getPosition().x > 256 && player.getPosition().x < 320 && player.getPosition().y >32 && player.getPosition().y < 192)
	{
		input.setKeyUp(sf::Keyboard::E);

		state = GameState::BOSS;

	}*/
}

void Game::update(float deltaTime)
{

#pragma region CameraUpdates
	//Updates camera target position if the player leaves the boundaries of the viewport on the y axis
	if (player.getPosition().y < (player_view.getCenter().y - (player_view.getSize().y/2)))
	{
		targetCam = sf::Vector2f(player_view.getCenter().x, player_view.getCenter().y - screenHeight + 32);
	}
	else if (player.getPosition().y > (player_view.getCenter().y + (player_view.getSize().y / 2)))
	{
		targetCam = sf::Vector2f(player_view.getCenter().x, player_view.getCenter().y + screenHeight -32);
	}
	
	//If the camera current position doesnt match the taget position then begin interpolation until target position is reached
	if (player_view.getCenter() != targetCam)
	{
		player_view.setCenter(Interpolate(player_view.getCenter(), targetCam, 0.1f));
	}
	//Update the viewport
	window->setView(player_view);
#pragma endregion


#pragma region AgentsUpdates
	//Prevents the player from moving offscreen on the x-axis
	if (player.getPosition().x > screenWidth)
	{
		player.setPosition(screenWidth - player.getSize().x, player.getPosition().y);
		player.falling = true;
	}
	else if (player.getPosition().x < 0)
	{
		player.setPosition(0 + player.getSize().x, player.getPosition().y);
		player.falling = true;
	}
	
	//Update the player
	player.update(deltaTime);

	enemyTest.update(deltaTime);


	//FIXME enemy update
/*
	for (int i = 0; i < 4; i++)
	{
		enemy[i].update(deltaTime);
	}
*/

#pragma endregion

#pragma region Collisions
	//Tracks if a collision is detected
	bool colliding = false;

	//Checks for collision between the player and the base of the building 
	//and triggers the player collision response if necessary
	std::vector<Tile>* buildingB = buildingBase.getLevel();
	std::vector<int>* buildingBInt = buildingBase.getTileMap();

	for (int i = 0; i < (int)buildingB->size(); i++)
	{
		// if "alive" check collision
		if ((*buildingB)[i].isAlive())
		{
			if (checkCollision(&player, &(*buildingB)[i]))
			{
				int wall = 0;

				if (buildingBInt->at(i) == 6)
				{
					std::printf("Wall");
					wall = 1;
				}
				else if (buildingBInt->at(i) == 5)
				{
					std::printf("Floor");
					wall = 0;
				}

				colliding = true;
				
				player.collisionResponse(&(*buildingB)[i], wall);
			}

			if (checkCollision(&enemyTest, &(*buildingB)[i]))
			{
				if (buildingBInt->at(i) == 6)
				{
				//	std::printf("Wall");
				}
				else if (buildingBInt->at(i) == 5)
				{
			//		std::printf("Floor");

				}
				enemyTest.collisionResponse(&(*buildingB)[i]);
			}
		}
	}

	//Checks for collision between the player and the Right chunk of the building 
	//and triggers the player collision response if necessary
	std::vector<Tile>* buildingCR = buildingChunkR.getLevel();
	for (int i = 0; i < (int)buildingCR->size(); i++)
	{
		// if "alive" check collision
		if ((*buildingCR)[i].isAlive())
		{
			if (checkCollision(&player, &(*buildingCR)[i]))
			{
				colliding = true;
				player.collisionResponse(&(*buildingCR)[i], 0);
			}
		}
	}

	//Checks for collision between the player and the Left chunk of the building 
	//and triggers the player collision response if necessary
	std::vector<Tile>* buildingCL = buildingChunkL.getLevel();
	for (int i = 0; i < (int)buildingCL->size(); i++)
	{
		// if "alive" check collision
		if ((*buildingCL)[i].isAlive())
		{
			if (checkCollision(&player, &(*buildingCL)[i]))
			{
				colliding = true;
				player.collisionResponse(&(*buildingCL)[i],0);
			}
		}
	}

	//Checks for collision between the player and the ground outside of the building 
	//and triggers the player collision response if necessary
	std::vector<Tile>* gTile = ground.getLevel();
	for (int i = 0; i < (int)gTile->size(); i++)
	{
		// if "alive" check collision
		if ((*gTile)[i].isAlive())
		{
			if (checkCollision(&player, &(*gTile)[i]))
			{
				colliding = true;
				player.collisionResponse(&(*gTile)[i],0);
			}
		}
	}

	//If the player is colliding with nothing in the world, and therefore is in the air, set them to fall
	//Partially rectifies the climbing walls glitch, and makes this error more difficult to replicate/exploit
	if (colliding == false)
	{
		player.falling = true;
	}

	//FIXME check enemy collisions with the player
//for (int i = 0; i < 4; i++)
//{
//	if (checkCollision(&player, &enemy[i]))
//	{
//		//enemy[i].collisionResponse(&player);
//		//player.falling = true;
//	}
//}
#pragma endregion




	//FIXME player lives 
/*
	if (player.lives == 0)
	{
		player.setPosition(0, 0);
	}
*/
}

void Game::render()
{

	beginDraw();
	window->draw(baseBackObj);	
	window->draw(skyBackObj);

	ground.render(window);

	buildingBase.render(window);
	buildingChunkL.render(window);
	buildingChunkR.render(window);

	window->draw(player);

	//FIXME render enemies
	//for (int i = 0; i < 4; i++)
	//{
	//	window->draw(enemy[i]);
	//}
	//FIXME player lives render
	//window->draw(player.life);

	endDraw();

}

#pragma endregion

#pragma region UtilityFunctions
void Game::beginDraw()
{
	window->clear(sf::Color::Cyan);
}

void Game::endDraw()
{
	window->display();
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

//Setter for the screen width
void Game::setScreenWidth(int x)
{
	screenWidth = x;
}

//setter for the screen height
void Game::setScreenHeight(int y)
{
	screenHeight = y;
}

//Interpolation function used for the camera pan
sf::Vector2f Game::Interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor)
{
	if (factor > 1.0f)
	{
		factor = 1.0f;
	}
	else if (factor < 0.0f)
	{
		factor = 0.0f;
	}

	return pointA + (pointB - pointA)*factor;
}

GameState Game::getState()
{
	return state;
}
#pragma endregion