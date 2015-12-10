#pragma once
#include <iostream>

class Player
{
	std::string Name;
	enum class Color {YELLOW, BLUE, GREEN, LIGHT_BLUE};
	Color color;
	int money;
	int move;
	bool jail_card;


public:
	Player(){}
};