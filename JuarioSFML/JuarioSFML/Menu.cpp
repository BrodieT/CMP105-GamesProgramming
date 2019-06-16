#include "pch.h"
#include "Menu.h"



Menu::Menu(sf::RenderWindow* hwnd, Input* in)
{

	//store pointer to window and input class
	window = hwnd;
	input = in;

	if (!myFont.loadFromFile("../gfx/Fonts/TACOM___.ttf"))
	{
		std::printf("Error loading font");
	}


	menu.loadFromFile("../gfx/Backgrounds/MenuBackground.png");

	background.setTexture(&menu);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setPosition(0, 0);

	buttonBack.loadFromFile("../gfx/Backgrounds/ButtonBack.png");

	playButton.setTexture(&buttonBack);
	playButton.setSize(sf::Vector2f(175, 50));
	playButton.setPosition(sf::Vector2f(50, 250));

	controlsButton.setTexture(&buttonBack);
	controlsButton.setSize(sf::Vector2f(175, 50));
	controlsButton.setPosition(sf::Vector2f(50, 325));

	exitButton.setTexture(&buttonBack);
	exitButton.setSize(sf::Vector2f(175, 50));
	exitButton.setPosition(sf::Vector2f(50, 400));



	playText.setString("Play");
	playText.setPosition(sf::Vector2f(playButton.getPosition().x + (playButton.getSize().x/4), playButton.getPosition().y));
	playText.setFont(myFont);
	playText.setFillColor(sf::Color::Black);
	playText.setCharacterSize(30);

	controlsText.setString("Controls");
	controlsText.setPosition(sf::Vector2f(controlsButton.getPosition().x + 5, controlsButton.getPosition().y));
	controlsText.setFont(myFont);
	controlsText.setFillColor(sf::Color::Black);
	controlsText.setCharacterSize(30);

	exitText.setString("Exit");
	exitText.setPosition(sf::Vector2f(exitButton.getPosition().x + (exitButton.getSize().x / 4), exitButton.getPosition().y));
	exitText.setFont(myFont);
	exitText.setFillColor(sf::Color::Black);
	exitText.setCharacterSize(30);


	tileTxt.setString("Juario");
	tileTxt.setPosition(sf::Vector2f(50, 100));
	tileTxt.setFont(myFont);

	sf::Color orange;
	orange.r = 255;
	orange.g = 140;
	orange.b = 0;
	
	tileTxt.setFillColor(orange);
	tileTxt.setCharacterSize(100);
	


	state = GameState::MENU;
}


Menu::~Menu()
{
}


void Menu::update(float deltaTime)
{
	
	
	
	
}

void Menu::handleInput(float deltaTime)
{
	//Play Button
	if (playButton.getGlobalBounds().contains(sf::Vector2f(input->getMouseX(), input->getMouseY())) && input->isMouseDown() == true)
	{
		input->setMouseDown(false);

		state = GameState::LEVEL;
	}

	//Controls Button
	if (controlsButton.getGlobalBounds().contains(sf::Vector2f(input->getMouseX(), input->getMouseY())) && input->isMouseDown() == true)
	{
		state = GameState::CONTROLS;
	}

	//Exit Button
	if (exitButton.getGlobalBounds().contains(sf::Vector2f(input->getMouseX(), input->getMouseY())) && input->isMouseDown() == true)
	{
		window->close();
	}

}

void Menu::render()
{

	beginDraw();
	window->draw(background);
	window->draw(playButton);
	window->draw(playText);

	window->draw(controlsButton);
	window->draw(controlsText);

	window->draw(exitButton);
	window->draw(exitText);

	window->draw(tileTxt);

	endDraw();

}

void Menu::beginDraw()
{
	window->clear(sf::Color::Cyan);
}

void Menu::endDraw()
{
	window->display();
}

GameState Menu::getState()
{
	return state;
}