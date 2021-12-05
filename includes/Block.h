#pragma once


#include <SFML/Graphics.hpp>


using std::pair;


class Block: public sf::RectangleShape {
public:
	pair<int, int> pos;

	Block (pair<int, int> pos, sf::Color color);
	void move (pair<int, int> pos);
};