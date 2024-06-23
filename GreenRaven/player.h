#pragma once
#include "object.h"
#include "fruit.h"
#include "bomb.h"
#include "SFML/Graphics.hpp"

class player : public object {
private:
	int speed = 8;
	sf::Sprite sprite;
	sf::Texture tex;
	int textNum = 0;
	bool walking = 0;
	int walkingtimer = 0;
	int eatingtimer = 0;
	int damagetimer = 0;
	bool takingdamage = 0;
	int animationStatus();
public:
	const int  walkingTimerreset = 10;
	const int eatingTimerreset = 83;
	const int damageTimerreset = 60;
	player(int sx, int sy);
	void tick();
	void render(sf::RenderWindow* window);
	bool intersects(object* obj);
	void setDamagetimer(int frames);
	void setEatingtimer(int frames);
	bool isTakingDamage();
	bool isEating();
};