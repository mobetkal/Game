#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ButtonText
{
	sf::Text button_text;
	GameState state;
	bool SetStyle;
public:
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float y, GameState state, bool SetStyle = true)
		:
		button_text(text, font, characterSize),
		state(state),
		SetStyle(SetStyle)
	{
		button_text.setPosition((1100 / 2 - button_text.getGlobalBounds().width / 2), y);
		button_text.setColor(sf::Color::Black);
	}
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float x, float y, GameState state, bool SetStyle = true)
		:
		button_text(text, font, characterSize),
		state(state),
		SetStyle(SetStyle)
	{
		button_text.setPosition(x, y);
		button_text.setColor(sf::Color::Black);
	}
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float x, float y, bool SetStyle = true)
		:
		button_text(text, font, characterSize),
		SetStyle(SetStyle)
	{
		button_text.setPosition(x, y);
		button_text.setColor(sf::Color::Black);
	}
	ButtonText(const sf::String& text, const sf::Font& font, unsigned int characterSize, float y, bool SetStyle = true)
		:
		button_text(text, font, characterSize),
		SetStyle(SetStyle)
	{
		button_text.setPosition((1100 / 2 - button_text.getGlobalBounds().width / 2), y);
		button_text.setColor(sf::Color::Black);
	}
	sf::Text& GetText()
	{
		return button_text;
	}
	GameState GetState() const
	{
		return state;
	}
	bool MakeStyle()
	{
		return SetStyle;
	}
	void SetString(std::string newString)
	{
		button_text.setString(newString);
	}
};