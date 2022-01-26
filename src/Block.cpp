#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Config.h"


Block::Block (std::pair<int, int> pos, sf::Color color) {
	this->setPos({pos.first, pos.second});
	this->setSize(sf::Vector2f(BS, BS));
	this->setFillColor(color);
}

std::pair<int, int> Block::getPos () {
	return this->pos;
}

void Block::setPos (std::pair<int, int> pos) {
	this->pos = pos;

	int x = pos.first * (BS + GSS);
	int y = pos.second * (BS + GSS);
	this->setPosition(x, y);
}