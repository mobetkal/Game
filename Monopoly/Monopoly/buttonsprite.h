#pragma once
#include <utility>
#include "game.h"

class ButtonSprite
{
	sf::Sprite button_sprite;
	GameState state;
	bool visible;
	std::pair<sf::Texture, sf::Texture> texture;
public:
	ButtonSprite(std::pair<sf::Texture, sf::Texture> texture, float x, float y, GameState state, bool visibility = true)
		:
		state(state),
		visible(visibility)
	{
		texture.first.setSmooth(true);
		texture.second.setSmooth(true);
		this->texture.first = texture.first;
		this->texture.second = texture.second;
		button_sprite.setPosition(x, y);
	}
	std::pair<sf::Texture, sf::Texture>& GetTexture()
	{
		return texture;
	}
	sf::Sprite& GetSprite()
	{
		return button_sprite;
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