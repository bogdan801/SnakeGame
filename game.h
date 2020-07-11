#pragma once
#include "cell.h"

class game{
public:
	game();
	game(int W,int H);
	void update(sf::RenderWindow& win, sf::Sprite& whiteS, sf::Sprite& redS, sf::Sprite& greenS);
private:
	sf::Font font;
	sf::Text t;
	const int W, H;
	cell** cells;
	std::vector<sf::Vector2i> snake;
	sf::Vector2i head;
	sf::Vector2i dir;
	sf::Vector2i fruit;
	sf::Clock clk;
	bool pause = false;
	bool tick(float lim);
	void direction();
	void startingPos();
	void setFruit();
};

