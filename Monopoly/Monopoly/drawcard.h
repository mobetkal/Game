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
	virtual void DrawCardAction(Player& activePlayer) = 0;

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
		SetUsed(true);
	}
};
class GoToPoint : public DrawCard
{
	int area;
	int money;
	bool pickMoney;

public:
	GoToPoint(const sf::String& description, int area, int money, bool pickMoney = false)
		:
		DrawCard(description),
		area(area),
		pickMoney(pickMoney),
		money(money)
	{}

	void DrawCardAction(Player& activePlayer) override
	{
		int movePawn = 0;
		if (area > activePlayer.GetPawn().GetArea())
			movePawn = area - activePlayer.GetPawn().GetArea();
		else
			movePawn = 40 - activePlayer.GetPawn().GetArea() + area;

		if(activePlayer.GetPawn().move(movePawn) && pickMoney)
			activePlayer.AddMoney(money);
		activePlayer.SetActiveField(true);
		SetUsed(true);
	}
};
class GoOutFromJail : public DrawCard
{
public:
	GoOutFromJail(const sf::String& description)
		:
		DrawCard(description)
	{}

	void DrawCardAction(Player& activePlayer) override
	{
		activePlayer.SetJailCard(true);
		SetUsed(true);
	}
};
class GoToJail : public DrawCard
{
public:
	GoToJail(const sf::String& description)
		:
		DrawCard(description)
	{}

	void DrawCardAction(Player& activePlayer) override
	{
		activePlayer.SetBlock(2, true);
		/*activePlayer.SetActiveMovement(false);
		activePlayer.SetDoublet(false);*/
		SetUsed(true);
	}
};