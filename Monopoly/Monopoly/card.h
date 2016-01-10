#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>
#include "rent.h"
#include "player.h"
#include "game.h"

class Chance
{
	sf::String description;
	bool wasUsed;
public:
	Chance(const sf::String& description) 
		:
		description(description),
		wasUsed(false)
	{
		
	}
	sf::String& GetDescrition(){ return description; }
	bool cardWasUsed(){ return wasUsed; }
};

class DeedCard
{
	Player* owner;
	sf::Text title;
	Rent rents;
	unsigned int landPrice;
	unsigned int housePrice;
	unsigned int hotelPrice;
	unsigned int mortgage;

public:
	DeedCard(){}
	DeedCard(const sf::String& title, const sf::Font& font, Rent& rents, const unsigned int& landPrice, const unsigned int& housePrice, const unsigned int& hotelPrice, const unsigned int& mortgage)
		:
		title(title, font, 20),
		landPrice(landPrice),
		mortgage(mortgage),
		rents(rents),
		housePrice(housePrice),
		hotelPrice(hotelPrice),
		owner(nullptr)
	{}

	Player* GetOwner(){ return owner; }
	void SetOwner(Player& newOwner){ this->owner = &newOwner; }
	sf::Text& Get_title(){ return title; }
	Rent Get_rents(){ return rents; }
	unsigned int& Get_landPrice(){ return landPrice; }
	unsigned int& Get_housePrice(){ return housePrice; }
	unsigned int& Get_hotelPrice(){ return hotelPrice; }
	unsigned int& Get_mortgage(){ return mortgage; }
};

class TrainCard
{
	Player* owner;
	sf::Text title;
	unsigned int CardPrice;
	unsigned int rent;
	unsigned int mortgage;

public:
	TrainCard(){}
	TrainCard(const sf::String& title, const sf::Font& font, const unsigned int& Price, const unsigned int& Rent, const unsigned int& mortgage)
		:
		title(title, font, 22),
		CardPrice(Price),
		rent(Rent),
		mortgage(mortgage),
		owner(nullptr)
	{}

	sf::String ShowRents()
	{
		return ("  " + (sf::String)std::to_string(rent) + L" zł\n  " + (sf::String)std::to_string(rent * 2) + L" zł\n " + (sf::String)std::to_string(rent * 4) + L" zł\n" + (sf::String)std::to_string(rent * 8) + L" zł");
	}
	Player* GetOwner(){ return owner; }
	void SetOwner(Player& newOwner){ this->owner = &newOwner; }
	sf::Text& Get_title(){ return title; }
	unsigned int& Get_CardPrice(){ return CardPrice; }
	unsigned int& Get_Rent(){ return rent; }
	unsigned int& Get_mortgage(){ return mortgage; }
};

class SpecialCard
{
	Player* owner;
	sf::Text title;
	unsigned int CardPrice;
	unsigned int mortgage;

public:
	SpecialCard(){}
	SpecialCard(const sf::String& title, const sf::Font& font, const unsigned int& Price, const unsigned int& mortgage)
		:
		title(title, font, 22),
		CardPrice(Price),
		mortgage(mortgage),
		owner(nullptr)
	{}

	Player* GetOwner(){ return owner; }
	void SetOwner(Player& newOwner){ this->owner = &newOwner; }
	sf::Text& Get_title(){ return title; }
	unsigned int& Get_CardPrice(){ return CardPrice; }
	unsigned int& Get_mortgage(){ return mortgage; }
};