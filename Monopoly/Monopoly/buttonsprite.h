#pragma once
#include <utility>
#include <iostream>
#include <SFML/Graphics.hpp>

class ButtonSprite
{
	sf::Sprite button_sprite;
	GameState state;
	std::pair<sf::Texture, sf::Texture> pair_texture;
	sf::Texture texture;

public:
	ButtonSprite(std::pair<sf::Texture, sf::Texture> texture, float x, float y, GameState state)
		:
		state(state)
	{
		texture.first.setSmooth(true);
		texture.second.setSmooth(true);
		this->pair_texture.first = texture.first;
		this->pair_texture.second = texture.second;
		button_sprite.setPosition(x, y);
	}
	ButtonSprite(sf::Texture& texture, float x, float y)
		:
		texture(texture)
	{
		texture.setSmooth(true);
		button_sprite.setPosition(x, y);
		button_sprite.setTexture(texture);
	}
	std::pair<sf::Texture, sf::Texture>& GetTexture() { return pair_texture; }
	sf::Sprite& GetSprite() { return button_sprite; }
	GameState GetState() const { return state; }
};