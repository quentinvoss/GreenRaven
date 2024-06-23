#pragma once
#include "object.h"
#include "SFML/Graphics.hpp"

class bomb : public object {
private:
	sf::Sprite sprite;
	sf::Texture tex;
	int gravity = 3;
	int frame = 0;
	const int  timerreset = 8;
	int timer = timerreset;
public:
	bomb(int sx, int sy) {
		this->setX(sx);
		this->setY(sy);
		tex.loadFromFile("textureAtlas.png");
		sprite.setTexture(tex);
		sprite.setTextureRect(sf::IntRect(20 * frame, 60, 20, 20));
		sprite.scale(sf::Vector2f(this->getScale(), this->getScale()));
		sprite.setPosition(sf::Vector2f(this->getX(), this->getY()));
	}
	~bomb() {

	}
	void tick() {
		timer--;
		if (timer == 0) {
			frame = (frame + 1) % 3;
			sprite.setTextureRect(sf::IntRect(20 * frame, 60, 20, 20));
			timer = timerreset;
		}
		sprite.setPosition(sf::Vector2f(this->getX(), this->getY()));
		this->setY(this->getY() + gravity);
	}
	void render(sf::RenderWindow* window) {
		window->draw(sprite);
	}
};