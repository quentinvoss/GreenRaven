#pragma once
#include <vector>
#include "player.h"
#include "fruit.h"
#include "bomb.h"
#include <time.h>
#include "aMath.h"
#include "displaytext.h"




namespace ge {
	player p(360, 720);
	std::vector<fruit*> food;
	std::vector<bomb*> bombs;
	double intervall = 3;
	double ftimerreset = 60 * intervall;
	int ftimer = ftimerreset;
	int score = 0;
	int lives = 3;
	int gameTime = 0;
	displaytext* scoreText = new displaytext(std::to_string(score));
	displaytext* livesText = new displaytext(std::to_string(lives));

	void init() {
		srand(time(NULL));
		scoreText->setPosition(sf::Vector2f(800, 0), 3);
	}

	void tick() {
		ftimer--;
		gameTime++;
		p.tick();
		if (ftimer == 0) {
			int r1 = rand() % 361;
			int r2 = rand() % 361;
			int xCoord = r1 + r2;
			if (rand() % 5 == 0) {
				bombs.push_back(new bomb(rand() % 720, -100));
			}
			else {
				food.push_back(new fruit(rand() % 720, -100, rand() % 5));
			}
			intervall = 3 - float(gameTime) / (10000 * 2);
			if (intervall < 0.02) {
				intervall = 0.02;
			}
			ftimerreset = 60 * intervall;
			ftimer = ftimerreset;
		}
		for (int i = 0; i < food.size(); i++) {
			food[i]->tick();
			if (food[i]->getY() > 1000) {
				delete food[i];
				food.erase(std::next(food.begin(), i));
			}
		}
		for (int i = 0; i < bombs.size(); i++) {
			bombs[i]->tick();
			if (bombs[i]->getY() > 1000) {
				delete bombs[i];
				bombs.erase(std::next(bombs.begin(), i));
			}
		}

		for (int i = 0; i < food.size(); i++) {
			if (p.intersects(food[i])) {
				delete food[i];
				food.erase(std::next(food.begin(), i));
				delete scoreText;
				score += 50;
				scoreText = 0;
				scoreText = new displaytext(std::to_string(score));
				scoreText->setPosition(sf::Vector2f(800, 0), 3);
				if (!p.isTakingDamage() && !p.isEating()) {
					p.setEatingtimer(p.eatingTimerreset);
				}
			}
		}
		for (int i = 0; i < bombs.size(); i++) {
			if (p.intersects(bombs[i])) {
				p.setDamagetimer(p.damageTimerreset);
				delete bombs[i];
				bombs.erase(std::next(bombs.begin(), i));
				lives--;
				delete livesText;
				livesText = 0;
				livesText = new displaytext(std::to_string(lives));
			}
		}
	}
	void render(sf::RenderWindow* window) {
		p.render(window);
		for (auto i : food) {
			i->render(window);
		}
		for (auto i : bombs) {
			i->render(window);
		}
		scoreText->render(window);
		livesText->render(window);
	}
}