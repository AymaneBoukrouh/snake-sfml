#include <SFML/Graphics.hpp>
#include "MainWindow.h"
#include "Snake.h"
#include "Config.h"


MainWindow::MainWindow () {
	this->width = (BS+GSS) * (GXS-1);
	this->height = (BS+GSS) * (GYS-1);

	this->snake = new Snake();

	this->create(
		sf::VideoMode(this->width, this->height),
		"Snake in C++"
	);
}

void MainWindow::run () {
	while (this->isOpen()) {
		sf::Event event;
		while (this->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					snake->change_direction("left");

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					snake->change_direction("up");

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					snake->change_direction("right");

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					snake->change_direction("down");


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					if (snake->is_dead) snake->reset();
					else if (snake->is_moving) snake->stop_mouvement();
					else snake->start_mouvement();
				}
			}

			if (event.type == sf::Event::Closed) {
				this->snake->stop_mouvement();
				this->close();
			}
		}

		this->clear(sf::Color::White);
		this->snake->draw(this);
		this->display();
	}
}