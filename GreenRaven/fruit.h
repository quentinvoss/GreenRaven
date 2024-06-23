#pragma once
#include "object.h"
#include "SFML/Graphics.hpp"

class fruit : public object {
private:
	sf::Sprite sprite;
	sf::Texture tex;
	int gravity = 3;
public:
	fruit(int sx, int sy, int type) {
		this->setX(sx);
		this->setY(sy);
		tex.loadFromFile("textureAtlas.png");
		sprite.setTexture(tex);
		sprite.setTextureRect(sf::IntRect(20 * type, 40, 20, 20));
		sprite.scale(sf::Vector2f(this->getScale(), this->getScale()));
		sprite.setPosition(sf::Vector2f(this->getX(), this->getY()));
	}
	~fruit() {

	}
	void tick() {
		sprite.setPosition(sf::Vector2f(this->getX(), this->getY()));
		this->setY(this->getY() + gravity);
	}
	void render(sf::RenderWindow* window) {
		window->draw(sprite);
	}
};