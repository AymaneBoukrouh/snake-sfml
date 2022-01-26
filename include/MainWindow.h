#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Config.h"


class MainWindow: public sf::RenderWindow {
private:
	int width, height;
	Snake *snake;

public:
	MainWindow ();
	void run ();
};