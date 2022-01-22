#pragma once

#include <SFML/Graphics.hpp>


class Block: public sf::RectangleShape {
private:
	std::pair<int, int> pos;

public:
	Block (std::pair<int, int> pos, sf::Color color);
	std::pair<int, int> getPos ();
	void setPos (std::pair<int, int> pos);
};