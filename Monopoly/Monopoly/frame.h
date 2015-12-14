#pragma once
#include "game.h"

class Frame
{
	sf::Sprite frame;
	sf::Text name;
	bool active;
public:
	Frame(sf::Texture texture, unsigned int x, unsigned int y, sf::Font font, unsigned int size, bool active = false)
		:
		name("", font, size)
	{
		texture.setSmooth(true);
		frame.setTexture(texture);
		frame.setPosition(x, y);
		name.setPosition(x + 18, y + 5);
		name.setColor(sf::Color::Black);
	}
	sf::Text& GetText()
	{
		return name;
	}
	void SetText(std::string name)
	{
		this->name.setString(name);
	}
	bool IsActive() const
	{
		return active;
	}
	void TurnActive(bool set)
	{
		active = set;
	}
};