#pragma once
#include "minicard.h"

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