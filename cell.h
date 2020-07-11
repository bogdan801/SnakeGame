#pragma once
class cell{
public:
	sf::Vector2f position;

	int active = 0;
	cell();
	cell(sf::Vector2f position);
};

