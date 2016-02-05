#pragma once
#include "pawn.h"
#include "cardstatus.h"
#include "graphics.h"

class Player : public sf::Drawable, public sf::Transformable
{
	sf::Text name;
	sf::Text moneyStatus;
	sf::Text JailCardTitle;
	Pawn pawn;
	int money;
	bool existJailCard;
	bool activeMovement;
	bool active;
	bool doublet;
	bool activeField;
	bool bankrutpcy;
	bool winner;
	int blockMovement;
	std::vector<CardStatus*> Cards;
	sf::Sprite JailCard;
	std::vector<sf::Texture> MiniCardsTexture;
	Graphics graphics;
	unsigned int PlayerID;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(name);
		target.draw(moneyStatus);
			
		for (auto& test : Cards)
		{
			for (auto& card : test->GetVectorCards())
			{
				if (card.GetBusy())
					target.draw(card.GetVertCard());
				else
				{
					states.texture = &card.GetMiniCardTexture();
					target.draw(card.GetVertCard(), states);
				}
			}
		}
	}

public:
	Player(sf::Text& name, Pawn& pawn, unsigned int ID, Graphics& graphics);
	Player(Player&& rhs);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	~Player()
	{
		for (auto& card : Cards)
			delete card;
	}
	sf::Text& GetMoneyStatus(){ return moneyStatus; }
	sf::Text& GetJailCardTitle(){ return JailCardTitle; }
	sf::Sprite& GetJailCard(){ return JailCard; }
	bool ExistJailCard(){ return existJailCard; }
	void SetJailCard(bool set){ existJailCard = set; }
	std::vector<CardStatus*>& GetCardsStatus(){ return Cards; }
	void operator--();
	bool SpendMoney(int value, bool use = true);
	void AddMoney(int value);
	int IsBlocked()	{ return blockMovement; }
	void SetBlock(int rounds, bool Jail = false);
	int AccoundStatus()	{ return money;	}
	bool ThrewDoublet() { return doublet; }
	void SetDoublet(bool doublet) { this->doublet = doublet; }
	Pawn& GetPawn()	{ return pawn; }
	void SetActiveMovement(bool move) {	activeMovement = move; }
	bool IsActiveMovement()	{ return activeMovement; }
	void SetActive(bool active) { this->active = active; }
	bool IsActive() { return active; }
	void SetActiveField(bool active) { this->activeField = active; }
	bool IsActiveField() { return activeField; }
	sf::String GetString() { return name.getString(); }
	unsigned int GetID(){ return PlayerID; }
	void WinnerPlayer(){ winner = true; }
	bool IsWinner(){ return winner; }
	void BankruptcyPlayer();
	bool IsBankrupt(){ return bankrutpcy; }
};