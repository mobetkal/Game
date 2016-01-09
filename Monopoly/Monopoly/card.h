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
public:
	Chance(const sf::String& description) :description(description){}
	sf::String& GetDescrition(){ return description; }
};


class SpecialCard
{
	Player* owner;
	sf::String title;
	unsigned int landPrice;
	unsigned int mortgage;

public:
	SpecialCard(){}
	SpecialCard(const sf::String& title, unsigned int landPrice, unsigned int mortgage)
		:
		title(title),
		landPrice(landPrice),
		mortgage(mortgage),
		owner(nullptr)
	{}
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