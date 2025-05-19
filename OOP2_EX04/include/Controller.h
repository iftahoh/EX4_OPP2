#pragma once
#include <SFML/Graphics.hpp>
#include <Macros.h>
#include <Menu.h>

class Controller
{
public:
	Controller();
	~Controller() = default;
	void run();

private:
	sf::RenderWindow m_window;
	Menu m_menu;
};

