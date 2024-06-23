#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>

class displaytext {
private:
	sf::Text t;
	sf::Font f;
	std::string str = "";
	std::vector<std::string> words;
public:
	displaytext(std::string tstr) {
		str = tstr;
		std::stringstream ss(str);
		std::string temp = "";
		while (std::getline(ss, temp, ' ')) {
			words.push_back(temp);
			temp = "";
		}
		f.loadFromFile("arial.ttf");
		t.setFont(f);
		t.setFillColor(sf::Color::White);
		t.setCharacterSize(25);
		temp = "";
		for (std::string it : words) {
			temp += it;
			temp += " ";
		}
		if (temp.size() > 40) {
			t.setCharacterSize(12);
		}
		t.setString(temp);
	}
	void render(sf::RenderWindow* window) {
		window->draw(t);
	}
	//1: Center 2: Top Left 3: Top Right
	void setPosition(sf::Vector2f v, int mode) {
		switch (mode) {
		case 1:
			t.setPosition(sf::Vector2f(v.x - t.getLocalBounds().width / 2, v.y - t.getLocalBounds().height / 2));
			break;
		case 2:
			t.setPosition(v);
			break;
		case 3:
			t.setPosition(sf::Vector2f(v.x - t.getLocalBounds().width, v.y));
			break;
		}
	}
};