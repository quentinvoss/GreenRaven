#include <iostream>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "displaytext.h"
#include "player.h"
#include "fruit.h"
#include "handler.h"

const int Framerate = 60;
constexpr unsigned short FRAME_DURATION = int(1000000 / Framerate);

int main() {
	unsigned lag = 0;

	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	previous_time = std::chrono::steady_clock::now();

	int x = 800;
	int y = 800;

	sf::RenderWindow window;
	ge::init();
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(x, y));
	r.setFillColor(sf::Color(150, 150, 150));

	window.create(sf::VideoMode(x, y), "GreenRaven");
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - x) / 2, (sf::VideoMode::getDesktopMode().height - x) / 2));

	window.setKeyRepeatEnabled(true);
	sf::Mouse::setPosition(sf::Vector2i(250 + window.getPosition().x, 250 + window.getPosition().y));
	//Main Loop
	while (window.isOpen()) {



		//Get the difference in time between the current frame and the previous frame
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		//Add the difference to the lag
		lag += delta_time;

		//In other words, we're updating the current time for the next frame.
		previous_time += std::chrono::microseconds(delta_time);

		sf::Event Event;



		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;
			while (window.pollEvent(Event)) {
				switch (Event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			if (FRAME_DURATION > lag) {
				window.clear();
				window.draw(r);
				ge::tick();
				ge::render(&window);
				if (ge::lives == 0) {
					window.close();
				}
				window.display();

			}
		}
	}
	std::cout << "You are dead.\n";
	system("pause");
	return 0;
}