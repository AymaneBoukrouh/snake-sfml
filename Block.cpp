#include "Config.h"
#include "Block.h"
#include <SFML/Graphics.hpp>


using std::pair;


Block::Block (pair<int, int> pos, sf::Color color) {
	this->move({pos.first, pos.second});
	this->setSize(sf::Vector2f(BS, BS));
	this->setFillColor(color);
}


void Block::move (pair<int, int> pos) {
	this->pos = pos;

	int x = pos.first * (BS + GSS);
	int y = pos.second * (BS + GSS);
	this->setPosition(x, y);
}