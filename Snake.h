#pragma once


#include "Block.h"


using std::pair;
using std::vector;
using std::string;


class Snake {
public:
	Block *bait;
	vector<Block> blocks;
	string direction = "right";
	bool is_moving = false;
	bool is_dead = false;

	Snake ();
	void move ();
	void start_mouvement ();
	void change_direction (string direction);
	pair<int, int> generate_rand_pos ();
	void generate_bait ();
	void check_bait ();
	void check_game_over ();
	void reset ();
	bool exists (pair<int, int> b, vector<Block> blocks);
	Block *head ();
	Block *tail ();
};