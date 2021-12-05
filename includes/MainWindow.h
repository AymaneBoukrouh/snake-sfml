#pragma once


#include "Config.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>


class MainWindow: public sf::RenderWindow {
private:
	int
		WIDTH = (BS+GSS) * (GXS-1),
		HEIGHT = (BS+GSS) * (GYS-1);

	Snake snake;
	sf::Thread *snake_mouvement;

public:
	MainWindow ();
	void run ();
	void main_loop ();
};