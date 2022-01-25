#include <SFML/Graphics.hpp>
#include "../includes/Snake.h"
#include "../includes/Block.h"
#include "../includes/Config.h"


Snake::Snake () {
	this->init();
}

void Snake::init () {
	this->is_dead = false;
	this->is_moving = false;
	this->direction = "right";

	for (int i=0; i<SS; i++) {
		Block *block = new Block({SS-i-1, 5}, sf::Color::Red);
		this->blocks.push_back(block);
	}

	std::pair<int, int> pos = this->generate_rand_pos();
	this->bait = new Block(pos, sf::Color::Green);
}

void Snake::reset () {
	this->blocks.clear();
	this->init();
}

void Snake::draw (sf::RenderWindow *parent) {
	for (Block *block: this->blocks)
		parent->draw(*block);

	parent->draw(*(this->bait));
}

// *** Mouvement *** //

void Snake::change_direction (std::string direction) {
	if (
		this->direction == "right" && direction != "left" ||
		this->direction == "left" && direction != "right" ||
		this->direction == "up" && direction != "down" ||
		this->direction == "down" && direction != "up"
	) this->direction = direction;
}

void Snake::move () {
	std::pair<int, int> head_pos = this->head()->getPos();

	if (direction == "left") head_pos.first -= 1;
	else if (direction == "up") head_pos.second -= 1;
	else if (direction == "right") head_pos.first += 1;
	else if (direction == "down") head_pos.second += 1;

	if (head_pos.first>=GXS-1) head_pos.first = 0;
	if (head_pos.first<0) head_pos.first = GXS-2;
	if (head_pos.second>=GYS-1) head_pos.second = 0;
	if (head_pos.second<0) head_pos.second = GYS-2;

	this->tail()->setPos({head_pos.first, head_pos.second});
	Block *block = this->tail();
	this->blocks.pop_back();
	this->blocks.insert(this->blocks.begin(), block);
}

void Snake::start_mouvement () {
	this->is_moving = true;
	this->mouvement_thread = new sf::Thread([snake=this] { snake->loop_mouvement(); });
	this->mouvement_thread->launch();
}

void Snake::stop_mouvement () {
	this->is_moving = false;
	this->mouvement_thread->terminate();
}

void Snake::loop_mouvement () {
	this->move();
	sf::sleep(sf::milliseconds(DELAY));

	this->check_game_over();
	this->check_bait();

	if (this->is_moving && !this->is_dead) this->loop_mouvement();
}

// *** Game *** //

void Snake::generate_bait () {
	std::pair<int, int> pos = this->generate_rand_pos();
	this->bait->setPos(pos);
}

void Snake::check_bait () {
	std::pair<int, int> tail_pos = this->tail()->getPos();

	for (int i=0; i<this->blocks.size(); i++) {
		if (this->blocks[i]->getPos() == this->bait->getPos()) {
			Block *block = new Block(tail_pos, sf::Color::Red);
			this->blocks.push_back(block);
			this->generate_bait();
		}
	}
}

void Snake::check_game_over () {
	Block *head = this->head();

	for (int i=1; i<this->blocks.size(); i++)
		if (head->getPos() == this->blocks.at(i)->getPos()) {
			this->is_dead = true;
			for (Block *block: this->blocks)
				block->setFillColor(sf::Color::Black);

			return;
	}
}

// *** Helpers *** //

bool Snake::is_empty_cell (std::pair<int, int> b) {
	for (int i=0; i<this->blocks.size(); i++)
		if (b == this->blocks[i]->getPos())
			return false;
	return true;
}

std::pair<int, int> Snake::generate_rand_pos () {
	std::vector<std::pair<int, int>> empty_cells;

	for (int x=0; x<GXS-1; x++) {
		for (int y=0; y<GYS-1; y++) {
			if (this->is_empty_cell((std::pair<int, int>) {x, y}))
				empty_cells.push_back((std::pair<int, int>) {x, y});
		}
	}

	int r = rand() % empty_cells.size();
	return empty_cells[r];
}

Block* Snake::head () {
	return this->blocks[0];
}

Block* Snake::tail () {
	return this->blocks[this->blocks.size()-1];
}