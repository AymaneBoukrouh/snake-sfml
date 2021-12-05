#include "../includes/Config.h"
#include "../includes/Block.h"
#include "../includes/Snake.h"


using std::pair;
using std::vector;
using std::string;


Snake::Snake () {
	for (int i=0; i<SS; i++) {
		this->blocks.push_back(Block({SS-i-1, 5}, sf::Color::Red));
	}

	this->generate_bait();
}


void Snake::move () {
	pair<int, int> head_pos = this->head()->pos;

	if (direction == "left") head_pos.first -= 1;
	else if (direction == "up") head_pos.second -= 1;
	else if (direction == "right") head_pos.first += 1;
	else if (direction == "down") head_pos.second += 1;

	if (head_pos.first>=GXS-1) head_pos.first = 0;
	if (head_pos.first<0) head_pos.first = GXS-2;
	if (head_pos.second>=GYS-1) head_pos.second = 0;
	if (head_pos.second<0) head_pos.second = GYS-2;

	this->tail()->move({head_pos.first, head_pos.second});
	Block tmp = *this->tail();
	this->blocks.pop_back();
	this->blocks.insert(this->blocks.begin(), tmp);

	this->check_game_over();
	this->check_bait();
}


void Snake::start_mouvement () {
	if (this->is_moving && !this->is_dead) this->move();
	sf::sleep(sf::milliseconds(50));
	this->start_mouvement();
}


void Snake::change_direction (string direction) {
	if (
		this->direction == "right" && direction != "left" ||
		this->direction == "left" && direction != "right" ||
		this->direction == "up" && direction != "down" ||
		this->direction == "down" && direction != "up"
	) this->direction = direction;
}


pair<int, int> Snake::generate_rand_pos () {
	vector<pair<int, int>> empty_cells;

	for (int x=0; x<GXS-1; x++) {
		for (int y=0; y<GYS-1; y++) {
			if (not this->exists((pair<int, int>) {x, y}, this->blocks)) empty_cells.push_back((pair<int, int>) {x, y});
		}
	}

	int r = rand() % empty_cells.size();
	return empty_cells[r];
}


void Snake::generate_bait () {
	Block *bait = new Block(this->generate_rand_pos(), sf::Color::Green);
	this->bait = bait;
}


void Snake::check_bait () {
	pair<int, int> tail_pos = this->tail()->pos;

	for (int i=0; i<this->blocks.size(); i++) {
		if (this->blocks[i].pos == this->bait->pos) {
			Block *tmp = new Block(tail_pos, sf::Color::Red);
			this->blocks.push_back(*tmp);
			this->bait->move(this->generate_rand_pos());
		}
	}
}


void Snake::check_game_over () {
	Block *head = this->head();

	for (int i=1; i<this->blocks.size(); i++) if (head->pos == this->blocks[i].pos) {
		this->is_dead = true;
		for (int j=0; j<this->blocks.size(); j++) this->blocks[j].setFillColor(sf::Color::Black);
		break;
	}
}


void Snake::reset () {
	this->blocks.clear();
	this->is_dead = false;
	this->is_moving = false;
	this->direction = "right";

	for (int i=0; i<SS; i++) {
		this->blocks.push_back(Block({SS-i-1, 5}, sf::Color::Red));
	}

	this->generate_bait();
}


bool Snake::exists (pair<int, int> b, vector<Block> blocks) {
	for (int i=0; i<blocks.size(); i++) if (b == blocks[i].pos) return true;
	return false;
}


Block *Snake::head () {
	return &(this->blocks[0]);
}


Block *Snake::tail () {
	return &(this->blocks[this->blocks.size()-1]);
}