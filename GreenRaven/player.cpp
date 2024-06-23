#include "player.h"
#include "aMath.h"
#include <vector>

std::vector<sf::IntRect> rects;

player::player(int sx, int sy) {
	this->setX(sx);
	this->setY(sy);
	tex.loadFromFile("textureAtlas.png");
	sprite.setTexture(tex);
	sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
	sprite.scale(sf::Vector2f(this->getScale(), this->getScale()));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			rects.push_back(sf::IntRect(20 * j, 20 * i, 20, 20));
		}
	}
}
bool walkingSprite = 0;
int player::animationStatus() {
	if (walkingtimer != 0) {
		walkingtimer--;
	}
	if (walking && walkingtimer == 0) {
		walkingSprite = !walkingSprite;
		walkingtimer = walkingTimerreset;
	}
	if (!walking) {
		walkingSprite = 0;
	}
	if (eatingtimer == 0 && damagetimer == 0) {
		return walkingSprite;
	}
	if (damagetimer != 0) {
		damagetimer--;
		takingdamage = 1;
		if (damagetimer % 3 == 0) {
			takingdamage = 0;
		}
		return 5 * takingdamage + walkingSprite;
	}
	if (eatingtimer != 0) {
		int frameNum = 0;
		switch (int(eatingtimer / 6)) {
		case 13:
		case 9:
		case 5:
		case 1:
			frameNum = 2;
			break;
		case 12:
		case 10:
		case 8:
		case 6:
		case 4:
		case 2:
			frameNum = 3;
			break;
		case 11:
		case 7:
		case 3:
			frameNum = 4;
			break;
		default:
			frameNum = 2;
			eatingtimer = 1;
			break;
		}
		eatingtimer--;
		return frameNum + 5 * walkingSprite;
	}
	return 0;
}

void player::tick() {
	walking = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->setX(am::clampi(this->getX() - speed,0,720));
		walking = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->setX(am::clampi(this->getX() + speed, 0, 720));
		walking = 1;
	}
	sprite.setPosition(sf::Vector2f(this->getX(), this->getY()));
	sprite.setTextureRect(rects[animationStatus()]);
}
void player::render(sf::RenderWindow* window) {
	window->draw(sprite);
}
bool player::intersects(object* obj) {
	if (sprite.getGlobalBounds().intersects(sf::FloatRect(obj->getX(), obj->getY(), 20 * obj->getScale(), 20 * obj->getScale()))) {
		return 1;
	}
	return 0;
}
void player::setDamagetimer(int frames) {
	damagetimer = frames;
	eatingtimer = 0;
}
bool player::isTakingDamage() {
	return (damagetimer != 0);
}
bool player::isEating() {
	return (eatingtimer != 0);
}
void player::setEatingtimer(int frames) {
	eatingtimer = frames;
}