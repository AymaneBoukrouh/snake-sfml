#include <SFML/Graphics.hpp>

#define BS 20        // Block Size
#define SS 3         // Snake Size
#define GXS 40       // Grid X-Size
#define GYS 25       // Grid Y-Size
#define GSS 1        // Grid Separator Size

using std::pair;
using std::vector;
using std::string;


class Block: public sf::RectangleShape {
public:
	pair<int, int> pos;

	Block (pair<int, int> pos, sf::Color color) {
		this->move({pos.first, pos.second});
		this->setSize(sf::Vector2f(BS, BS));
		this->setFillColor(color);
	}

	void move (pair<int, int> pos) {
		this->pos = pos;

		int x = pos.first * (BS + GSS);
		int y = pos.second * (BS + GSS);
		this->setPosition(x, y);
	}
};


class Snake {
public:
	Block *bait;
	vector<Block> blocks;
	string direction = "right";
	bool is_moving = false;
	bool is_dead = false;

	Snake () {
		for (int i=0; i<SS; i++) {
			this->blocks.push_back(Block({SS-i-1, 5}, sf::Color::Red));
		}

		this->generate_bait();
	}

	void move () {
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

	void start_mouvement () {
		if (this->is_moving && !this->is_dead) this->move();
		sf::sleep(sf::milliseconds(50));
		this->start_mouvement();
	}

	void change_direction (string direction) {
		if (
			this->direction == "right" && direction != "left" ||
			this->direction == "left" && direction != "right" ||
			this->direction == "up" && direction != "down" ||
			this->direction == "down" && direction != "up"
		) this->direction = direction;
	}

	pair<int, int> generate_rand_pos () {
		vector<pair<int, int>> empty_cells;

		for (int x=0; x<GXS-1; x++) {
			for (int y=0; y<GYS-1; y++) {
				if (not this->exists((pair<int, int>) {x, y}, this->blocks)) empty_cells.push_back((pair<int, int>) {x, y});
			}
		}

		int r = rand() % empty_cells.size();
		return empty_cells[r];
	}

	void generate_bait () {
		Block *bait = new Block(this->generate_rand_pos(), sf::Color::Green);
		this->bait = bait;
	}

	void check_bait () {
		pair<int, int> tail_pos = this->tail()->pos;

		for (int i=0; i<this->blocks.size(); i++) {
			if (this->blocks[i].pos == this->bait->pos) {
				Block *tmp = new Block(tail_pos, sf::Color::Red);
				this->blocks.push_back(*tmp);
				this->bait->move(this->generate_rand_pos());
			}
		}
	}

	void check_game_over () {
		Block *head = this->head();

		for (int i=1; i<this->blocks.size(); i++) if (head->pos == this->blocks[i].pos) {
			this->is_dead = true;
			for (int j=0; j<this->blocks.size(); j++) this->blocks[j].setFillColor(sf::Color::Black);
			break;
		}
	}

	void reset () {
		this->blocks.clear();
		this->is_dead = false;
		this->is_moving = false;
		this->direction = "right";

		for (int i=0; i<SS; i++) {
			this->blocks.push_back(Block({SS-i-1, 5}, sf::Color::Red));
		}

		this->generate_bait();
	}

	bool exists (pair<int, int> b, vector<Block> blocks) {
		for (int i=0; i<blocks.size(); i++) if (b == blocks[i].pos) return true;
		return false;
	}

	Block *head () {
		return &(this->blocks[0]);
	}

	Block *tail () {
		return &(this->blocks[this->blocks.size()-1]);
	}
};


class MainWindow: public sf::RenderWindow {
public:
	int
		WIDTH = (BS+GSS) * (GXS-1),
		HEIGHT = (BS+GSS) * (GYS-1);

	Snake snake;
	sf::Thread *snake_mouvement;

	MainWindow () {
		this->create(
			sf::VideoMode(this->WIDTH, this->HEIGHT),
			"Snake in C++"
		);
	}

	void run () {
		auto *snake = &(this->snake);
		auto snake_mouvement_wrapper = [snake]() {
			snake->start_mouvement();
		};

		sf::Thread snake_mouvement(snake_mouvement_wrapper);
		snake_mouvement.launch();
		this->snake_mouvement = &snake_mouvement;

		this->main_loop();
	}

	void main_loop () {
		while (this->isOpen())
		{
			sf::Event event;
			while (this->pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.change_direction("left");
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.change_direction("up");
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.change_direction("right");
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.change_direction("down");

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						if (snake.is_dead) snake.reset();
						else snake.is_moving = not snake.is_moving;
					}
				}

				if (event.type == sf::Event::Closed) {
					this->snake_mouvement->terminate();
					this->close();
				}
			}

			this->clear(sf::Color::White);
			for (int i=0; i<snake.blocks.size(); i++) this->draw(snake.blocks[i]);
			this->draw(*(snake.bait));
			this->display();
		}
	}
};


int main()
{
	srand(time(NULL));
	auto mainWindow = new MainWindow();
	mainWindow->run();

	return 0;
}