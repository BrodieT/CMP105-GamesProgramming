#pragma once
#include <SFML/Graphics.hpp>

class Input
{
private:
	struct Mouse
	{
		int x, y;
		bool left;
	};

public:
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);
	bool isMouseDown();

	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	void setMouseDown(bool click);

	sf::Vector2f getMouseCoords(sf::RenderWindow* win);
	int getMouseX();
	int getMouseY();




private:

	bool keys[256]{ false };
	Mouse mouse;
};
