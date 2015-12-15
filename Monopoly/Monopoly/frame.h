#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Frame
{
	sf::Sprite frame;
	sf::Text text;
	std::string name;
	bool active;
public:
	Frame(sf::Texture& texture, float x, float y, const std::string& text, const sf::Font& font, unsigned int size, bool active = false)
		:
		text(text, font, size),
		active(active),
		name(text)
	{
		texture.setSmooth(true);
		frame.setTexture(texture);
		frame.setPosition(x, y);
		this->text.setPosition(x + 18, y + 5);
		this->text.setColor(sf::Color::Black);
	}
	std::string& GetString()
	{
		return name;
	}
	sf::Text& GetText()
	{
		return text;
	}
	sf::Sprite& GetSprite()
	{
		return frame;
	}
	void SetText(std::string name)
	{
		this->text.setString(name);
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