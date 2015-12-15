#pragma once
#include "game.h"

class ButtonText
{
	sf::Text button_text;
	GameState state;
	bool visible;
public:
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float y, GameState state, bool visibility = true)
		:
		button_text(text, font, characterSize),
		state(state),
		visible(visibility)
	{
		button_text.setPosition((1100 / 2 - button_text.getGlobalBounds().width / 2), y);
	}
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float x, float y, GameState state, bool visibility = true)
		:
		button_text(text, font, characterSize),
		state(state),
		visible(visibility)
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
	bool IsVisible() const
	{
		return visible;
	}
};