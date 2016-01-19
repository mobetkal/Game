#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Frame
{
	sf::Sprite frame;
	sf::Text text;
	std::string name;
	bool active;
	sf::Texture FrameTexture;
	sf::Texture activeFrameTexture;
	sf::Texture wrongFrameTexture;
public:
	Frame(sf::Texture& frameT, sf::Texture& activeT, sf::Texture& wrongT, float x, float y, const std::string& text, const sf::Font& font, unsigned int size, bool active = false)
		:
		text(text, font, size),
		active(active),
		name(text),
		FrameTexture(frameT),
		activeFrameTexture(activeT),
		wrongFrameTexture(wrongT)
	{
		FrameTexture.setSmooth(true);
		activeFrameTexture.setSmooth(true);
		wrongFrameTexture.setSmooth(true);
		frame.setTexture(frameT);
		frame.setPosition(x, y);
		this->text.setPosition(x + 18, y + 5);
		this->text.setColor(sf::Color::Black);
	}
	std::string& GetString() { return name; }
	sf::Text& GetText() { return text; }
	sf::Sprite& GetSprite() { return frame; }
	void SetText(std::string name) { this->text.setString(name); }
	bool IsActive() const { return active; }
	void TurnWrong() { frame.setTexture(wrongFrameTexture);	}
	void TurnActive(bool set) 
	{ 
		active = set; 
		if (active)
			frame.setTexture(activeFrameTexture);
		else
			frame.setTexture(FrameTexture);
	}

	void EnterTextIntoFrame(sf::Uint32& text)
	{
		if (text == 8 && name.size() != 0) // Backspace
		{
			name.pop_back();
			this->text.setString(name);
		}
		else if (text == 13) // Enter
			this->TurnActive(false);
		else if (text > 31 && text < 123 && name.size() < 14)
		{
			name.push_back((char)text);
			this->text.setString(name);
		}
	}
};