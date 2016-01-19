#pragma once
#include <utility>
#include <SFML/Graphics.hpp>

class ButtonSprite
{
	sf::Sprite button_sprite;
	GameState state;
	std::pair<sf::Texture, sf::Texture> pair_texture;
	sf::Texture texture;
	bool Active;

public:
	ButtonSprite(){}
	ButtonSprite(sf::Texture& texture1, sf::Texture& texture2, float x, float y, GameState state)
		:
		state(state)
	{
		texture1.setSmooth(true);
		texture2.setSmooth(true);
		this->pair_texture.first = texture1;
		this->pair_texture.second = texture2;
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
	ButtonSprite(const sf::Texture& enable, const sf::Texture& disable, float x, float y, bool active = true)
		:
		pair_texture(std::make_pair(enable, disable)),
		Active(active)
	{
		pair_texture.first.setSmooth(true);
		pair_texture.second.setSmooth(true);
		button_sprite.setPosition(x, y);
		if (Active)
			button_sprite.setTexture(enable);
		else
			button_sprite.setTexture(disable);
	}

	std::pair<sf::Texture, sf::Texture>& GetTexture() { return pair_texture; }
	sf::Sprite& GetSprite() { return button_sprite; }
	GameState GetState() const { return state; }
	void activeButton(bool active)
	{ 
		Active = active;
		if (Active)
			button_sprite.setTexture(pair_texture.first);
		else
			button_sprite.setTexture(pair_texture.second);
	}
	bool IsActive(){ return Active; }
};