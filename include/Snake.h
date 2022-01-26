#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Block.h"


class Snake {
public:
	std::string direction;
	std::vector<Block*> blocks;
	sf::Thread *mouvement_thread;
	Block *bait;

public:
	bool is_moving, is_dead;

	Snake ();
	void init ();
	void reset ();
	void draw (sf::RenderWindow *parent);

	// Mouvement
	void change_direction (std::string direction);
	void move ();
	void start_mouvement ();
	void stop_mouvement ();
	void loop_mouvement ();

	// Game
	void generate_bait ();
	void check_bait ();
	void check_game_over ();

	// Helpers
	bool is_empty_cell (std::pair<int, int> b);
	std::pair<int, int> generate_rand_pos ();
	Block* head ();
	Block* tail ();
};