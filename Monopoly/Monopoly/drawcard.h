#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class DrawCard
{
	sf::String description;
	bool wasUsed;

public:
	DrawCard(const sf::String& description, bool wasUsed = false)
		:
		description(description),
		wasUsed(wasUsed)
	{}
	virtual void DrawCardAction(Player& activePlayer){};

	sf::String& GetDescrition(){ return description; }
	bool cardWasUsed(){ return wasUsed; }
	void SetUsed(bool status){ wasUsed = status; }
};

class CashTransaction : public DrawCard
{
	int money;

public:
	CashTransaction(const sf::String& description, int money)
		:
		DrawCard(description),
		money(money)
	{}

	void DrawCardAction(Player& activePlayer) override
	{
		activePlayer.AddMoney(money);
	}
};