﻿#include <SFML\Graphics.hpp>
#include "player.h"

using namespace sf;

Player::Player(sf::Text& name, Pawn& pawn, unsigned int ID, Graphics& graphics)
	:
	name(name),
	pawn(pawn),
	money(1500),
	existJailCard(false),
	doublet(false),
	activeMovement(false),
	active(false),
	activeField(false),
	bankrutpcy(false),
	winner(false),
	blockMovement(0),
	PlayerID(ID),
	MiniCardsTexture(graphics.GetMiniCard()),
	moneyStatus("Stan konta: ", graphics.GetCardFont(), 16),
	graphics(graphics),
	JailCardTitle("Jail\nCard", graphics.GetCardFont(), 16)
{
	this->name.setPosition(710.0f, 133.0f + PlayerID * 100);
	this->name.setColor(sf::Color::Black);
	moneyStatus.setPosition(950.0f, 140.0f + PlayerID * 100);
	moneyStatus.setColor(sf::Color::Black);
	JailCardTitle.setPosition(715.0f, 54.0f);
	JailCardTitle.setColor(sf::Color::Black);

	Cards.emplace_back(new CardStatus(MiniCardsTexture[1], 4, sf::Color::Black, 700.0f, 160.0f, PlayerID));			// TRAINS
	Cards.emplace_back(new CardStatus(MiniCardsTexture[2], 2, sf::Color(149, 149, 149), 813.0f, 160.0f, PlayerID));	// SPECIAL
	Cards.emplace_back(new CardStatus(MiniCardsTexture[3], 2, sf::Color(78, 61, 113), 872.0f, 160.0f, PlayerID));	// PURPLE
	Cards.emplace_back(new CardStatus(MiniCardsTexture[4], 3, sf::Color(178, 194, 228), 931.0f, 160.0f, PlayerID));	// LIGHT BLUE
	Cards.emplace_back(new CardStatus(MiniCardsTexture[5], 3, sf::Color(177, 50, 95), 1017.0f, 160.0f, PlayerID));	// PINK

	Cards.emplace_back(new CardStatus(MiniCardsTexture[6], 3, sf::Color(243, 141, 77), 700.0f, 198.0f, PlayerID));	// ORANGE
	Cards.emplace_back(new CardStatus(MiniCardsTexture[7], 3, sf::Color(239, 59, 58), 786.0f, 198.0f, PlayerID));	// RED
	Cards.emplace_back(new CardStatus(MiniCardsTexture[8], 3, sf::Color(237, 247, 140), 872.0f, 198.0f, PlayerID));	// YELLOW
	Cards.emplace_back(new CardStatus(MiniCardsTexture[9], 3, sf::Color(83, 148, 114), 958.0f, 198.0f, PlayerID));	// GREEN
	Cards.emplace_back(new CardStatus(MiniCardsTexture[10], 2, sf::Color(56, 79, 146), 1044.0f, 198.0f, PlayerID));	// BLUE	

	JailCard.setTexture(MiniCardsTexture[0]);
	JailCard.setPosition(755.0f, 55.0f);
}
Player::Player(Player&& rhs)
	:
	name(rhs.name),
	pawn(std::move(rhs.pawn)),
	Cards(std::move(rhs.Cards)),
	money(rhs.money),
	existJailCard(rhs.existJailCard),
	doublet(rhs.doublet),
	activeMovement(rhs.activeMovement),
	active(rhs.active),
	activeField(rhs.activeField),
	bankrutpcy(rhs.bankrutpcy),
	winner(rhs.winner),
	blockMovement(rhs.blockMovement),
	PlayerID(rhs.PlayerID),
	MiniCardsTexture(rhs.MiniCardsTexture),
	moneyStatus(rhs.moneyStatus),
	graphics(rhs.graphics),
	JailCardTitle(rhs.JailCardTitle),
	JailCard(rhs.JailCard)
{}

void Player::operator--()
{
	if (blockMovement > 0)
		blockMovement -= 1;
}
bool Player::SpendMoney(int value, bool use)
{
	if ((money - value) >= 0)
	{
		if (use)
			money -= value;
		return true;
	}
	else
	{
		BankruptcyPlayer();
		return false;
	}
}
void Player::AddMoney(int value)
{
	money += value;
	if (money <= 0)
		BankruptcyPlayer();
}
void Player::SetBlock(int rounds, bool Jail)
{
	blockMovement = rounds;
	if (Jail)
	{
		pawn.GoToJail();
		activeMovement = false;
		doublet = false;
	}

}

void Player::BankruptcyPlayer()
{
	bankrutpcy = true;
}