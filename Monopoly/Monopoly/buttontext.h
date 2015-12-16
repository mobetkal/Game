#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ButtonText
{
	sf::Text button_text;
	GameState state;
public:
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float y, GameState state)
		:
		button_text(text, font, characterSize),
		state(state)
	{
		button_text.setPosition((1100 / 2 - button_text.getGlobalBounds().width / 2), y);
	}
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float x, float y, GameState state)
		:
		button_text(text, font, characterSize),
		state(state)
	{
		button_text.setPosition(x, y);
	}
	sf::Text& GetText()
	{
		return button_text;
	}
	GameState GetState() const
	{
		return state;
	}
};