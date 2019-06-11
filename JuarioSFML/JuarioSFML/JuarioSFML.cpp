#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Controls.h"
#include "Pause.h"
#include "Boss.h"
#include "States.h"

void main(int argc, char** argv[])
{
	int screenWidth = 1216;
	int screenHeight = 608;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Juario");
	Input input;
	//Gamestate
	Game game(&window, &input, screenWidth, screenHeight);
	Menu menu(&window, &input);
	Controls controls(&window, &input);
	Pause pause(&window, &input);
	Boss boss(&window, &input);
	GameState state = GameState::MENU;

	//for delta time
	sf::Clock clock;
	float deltaTime;


	while (window.isOpen())
	{

	

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
				//Lab2/////
			case sf::Event::KeyPressed:
				//update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}



		//if esc is pressed
		if (input.isKeyDown(sf::Keyboard::Escape))
		{
			input.setKeyUp(sf::Keyboard::Escape);
			window.close();
		}


		// Calculate delta time. How much time has passed since it was last calculated(in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();


		
		if (input.isKeyDown(sf::Keyboard::C) && state == GameState::MENU)
		{
			input.setKeyUp(sf::Keyboard::C);
			state = GameState::CONTROLS;
		}
		else if (input.isKeyDown(sf::Keyboard::C) && state == GameState::CONTROLS)
		{
			input.setKeyUp(sf::Keyboard::C);
			state = GameState::MENU;
		}
		else if (input.isKeyDown(sf::Keyboard::P) && state == GameState::LEVEL)
		{
			input.setKeyUp(sf::Keyboard::P);
			state = GameState::PAUSE;
		}
		else if (input.isKeyDown(sf::Keyboard::P) && state == GameState::PAUSE)
		{
			input.setKeyUp(sf::Keyboard::P);
			state = GameState::LEVEL;
		}
		


		switch (state)
		{
		case(GameState::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			state = menu.getState();
			break;
		case(GameState::LEVEL):
			//game loop
			game.handleInput(deltaTime, input);
			game.update(deltaTime);
			game.render();
			state = game.getState();
			break;
		case(GameState::CONTROLS):
			controls.handleInput(deltaTime);
			controls.update(deltaTime);
			controls.render();
			state = controls.getState();
			break;
		case(GameState::PAUSE):
			pause.handleInput(deltaTime);
			pause.update(deltaTime);
			pause.render();
			state = pause.getState();
			break;
		case(GameState::BOSS):
			boss.handleInput(deltaTime);
			boss.update(deltaTime);
			boss.render();
			state = boss.getState();
			break;
		}



		

	}
}