#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

class MiniCard
{
	sf::VertexArray VertCard;
	sf::Color Color;
	sf::Texture Texture;
	float x;
	float y;
	bool busy;

public:
	sf::VertexArray& GetVertCard(){ return VertCard; }
	sf::Texture& GetMiniCardTexture() { return Texture; }
	bool GetBusy(){ return busy; }
	MiniCard(const sf::Texture& Texture, const sf::Color& Color, const float& x, const float& y, bool busy = false)
		:
		VertCard(sf::Quads, 4),
		Color(Color),
		Texture(Texture),
		x(x),
		y(y),
		busy(busy)
	{
		VertCard[0].position = sf::Vector2f(x, y);				//left-top
		VertCard[1].position = sf::Vector2f(x + 24, y);			//right-top
		VertCard[2].position = sf::Vector2f(x + 24, y + 36);	//right-bottom
		VertCard[3].position = sf::Vector2f(x, y + 36);			//left-bottom
		SetCardStatusOwner(busy);
	}
	void SetCardStatusOwner(bool status)
	{
		this->busy = status;
		if (status)
		{
			VertCard[0].color = Color;
			VertCard[1].color = Color;
			VertCard[2].color = Color;
			VertCard[3].color = Color;
		}
		else
		{
			VertCard[0].texCoords = sf::Vector2f(0, 0);
			VertCard[1].texCoords = sf::Vector2f(24, 0);
			VertCard[2].texCoords = sf::Vector2f(24, 36);
			VertCard[3].texCoords = sf::Vector2f(0, 36);
		}
	}
};

class CardStatus
{
	std::vector<MiniCard> Cards;
	unsigned int playerID;
	int size;

public:
	std::vector<MiniCard>& GetVectorCards(){ return Cards; }

	CardStatus(const sf::Texture& Texture, const int size, const sf::Color Color, const float x, const float y, unsigned int& playerID)
		:
		size(size),
		playerID(playerID)
	{
		// x + i * 30, y + PlayerID * 100
		for (int i = 0; i < size; ++i)
		{
			Cards.emplace_back(Texture, Color, x + i * 27, y + playerID * 100);
		}
	}
};