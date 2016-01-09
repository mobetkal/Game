#pragma once
#include "card.h"
#include "game.h"
#include "buttontext.h"
#include <string>

sf::Vector2i ChooseCard(unsigned int area);

class Field
{
	unsigned int area;

public:
	Field(unsigned int area) : area(area){}
	virtual ~Field(){}
	unsigned int GetArea(){ return area; }
	//sf::Texture GetCardTexture(){ return cardGraphics; }
	virtual void ActionBuy(Player& player) = 0;
	virtual std::vector<ButtonSprite>& ShowGraphics() = 0;
	virtual std::vector<ButtonText>& ShowTexts() = 0;
	template<class Card>
	Card GetCard(){ return card; }
};

class ChanceField : public Field
{
	//list<Chance> cards;
	Chance card;

public:
	ChanceField(const Chance& card, const unsigned int& area) : card(card), Field(area){}
	void ActionBuy(Player& player) override
	{
		//cout << "Karta szansy" << endl;
	}
};

class SpecialField : public Field
{
	SpecialCard card;

public:
	SpecialField(const SpecialCard& card, const unsigned int& area) : card(card), Field(area){}
	void ActionBuy(Player& player) override
	{
		//cout << "Specialna karta" << endl;
	}
};

//class TrainField : public Field
//{
//	SpecialCard card;
//	unsigned int rent;
//
//public:
//	TrainField(const SpecialCard& card, const unsigned int& rent, const unsigned int& area) : card(card), rent(rent), Field(area){}
//	void Action() override
//	{
//		//cout << "pociag" << endl;
//	}
//	std::vector<sf::Sprite>& ShowGraphics() override
//	{
//		std::vector<sf::Sprite> graphics;
//		return graphics;
//	}
//};

class DeedField : public Field
{
	DeedCard card;
	std::vector<ButtonSprite> graphics;
	std::vector<ButtonText> texts;
	sf::Texture CardTexture;
	sf::Font CardFont;
	sf::VertexArray Color;

public:
	DeedField(const DeedCard& card, const sf::Texture& CardTexture, sf::Color color, const unsigned int& area)
		: 
		card(card), 
		CardTexture(CardTexture), 
		Field(area), 
		CardFont(*(this->card.Get_title().getFont())), // Problem długiego startu gry!!!
		Color(sf::Quads, 4)
	{
		Color[0].position = sf::Vector2f(220, 140); //left-top
		Color[1].position = sf::Vector2f(480, 140); //right-top
		Color[2].position = sf::Vector2f(480, 210); //right-bottom
		Color[3].position = sf::Vector2f(220, 210); //left-bottom
		for (int i = 0; i < 4; ++i)
			Color[i].color = color;
		this->CardTexture.setSmooth(true);
		texts.emplace_back(ButtonText(sf::Text(L"Tytuł Własności", CardFont, 16), sf::Color::Black, 145, false));
		texts.emplace_back(ButtonText(this->card.Get_title(), sf::Color::Black, 175, true));
		texts.emplace_back(ButtonText(sf::Text(L"CZYNSZ", CardFont, 16), sf::Color::Black, 250, false, -100.0));
		texts.emplace_back(ButtonText(sf::Text(L"- Teren niezabudowany\n- Z jednym domem\n- Z dwoma domami\n- Z trzema domami\n- Z HOTELEM", CardFont, 15), sf::Color::Black, 250, false, 8.0));
		texts.emplace_back(ButtonText(sf::Text(this->card.Get_rents().ShowRents(), CardFont, 15), sf::Color::Black, 225, true, 106.0f));
		texts.emplace_back(ButtonText(sf::Text(L"----------------------------------------------------", CardFont, 15), sf::Color::Black, 370, false));
		texts.emplace_back(ButtonText(sf::Text(L"Ceny domów -", CardFont, 15), sf::Color::Black, 390, false, -83.0f));
		texts.emplace_back(ButtonText(sf::Text((sf::String)(std::to_string(this->card.Get_housePrice())) + L" zł każdy", CardFont, 15), sf::Color::Black, 390, true, 82.0f));
		texts.emplace_back(ButtonText(sf::Text(L"Ceny hoteli -", CardFont, 15), sf::Color::Black, 430, false, -88.0f));
		texts.emplace_back(ButtonText(sf::Text("    " + (sf::String)(std::to_string(this->card.Get_hotelPrice())) + L" zł plus\ncena 3 domów", CardFont, 15), sf::Color::Black, 425, true, 75.0f));
		texts.emplace_back(ButtonText(sf::Text(L"Wartość HIPOTECZNA działki", CardFont, 15), sf::Color::Black, 480, false, -34.0f));
		texts.emplace_back(ButtonText(sf::Text((sf::String)(std::to_string(this->card.Get_mortgage())) + L" zł", CardFont, 15), sf::Color::Black, 480, true, 104.0f));
		texts.emplace_back(ButtonText(sf::Text(L"  2016 Marcin Obetkał", CardFont, 12), sf::Color::Black, 559, true));
	}
	sf::VertexArray& GetColor(){ return Color; }
	template<class Card>
	Card& GetCard() { return card; }
	void ActionBuy(Player& player) override
	{
		if (card.GetOwner() == nullptr)
		{
			card.SetOwner(player);
			player.SpendMoney(card.Get_landPrice());
			sf::Vector2i Cords(ChooseCard(this->GetArea()));
			if (Cords.x != -1 && Cords.y != -1 )
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetCardStatusOwner(true);
		}
	}
	std::vector<ButtonSprite>& ShowGraphics() override
	{
		graphics.emplace_back(CardTexture, (700 - 290) / 2, 125.0f);
		return graphics;
	}
	std::vector<ButtonText>& ShowTexts() override {	return texts; }
};

//class DoSmthField : public Field
//{
//	ButtonSprite Sprite;
//	ButtonText Description;
//	sf::Texture CardTexture;
//	void(*function)(int);
//public:
//	DoSmthField(const sf::Texture& CardTexture, void(*function)(int), const unsigned int& area) 
//		: 
//		Field(area),
//		function(function)
//	{
//		this->function(2);
//	}
//	void Action() //override
//	{
//		function(2)
//	}
//};

sf::Vector2i ChooseCard(unsigned int area)
{
	switch (area)
	{
	case 1:	  return sf::Vector2i(2,0);
	case 3:	  return sf::Vector2i(2, 1);
	//case 5:	  return sf::Vector2i(0, 0); // Dworzec 1
	case 6:	  return sf::Vector2i(3, 0);
	case 8:	  return sf::Vector2i(3, 1);
	case 9:	  return sf::Vector2i(3, 2);
	case 11:  return sf::Vector2i(4, 0);
	//case 12:  return sf::Vector2i(1, 0); // ELEKTROWNIA
	case 13:  return sf::Vector2i(4, 1);
	case 14:  return sf::Vector2i(4, 2);
	//case 15:  return sf::Vector2i(0, 1); // Dworzec 2
	case 16:  return sf::Vector2i(5, 0);
	case 18:  return sf::Vector2i(5, 1);
	case 19:  return sf::Vector2i(5, 2);
	case 21:  return sf::Vector2i(6, 0);
	case 23:  return sf::Vector2i(6, 1);
	case 24:  return sf::Vector2i(6, 2);
	//case 25:  return sf::Vector2i(0, 2); // Dworzec 3
	case 26:  return sf::Vector2i(7, 0);
	case 27:  return sf::Vector2i(7, 1);
	//case 28:  return sf::Vector2i(1, 1); // WODOCIĄG
	case 29:  return sf::Vector2i(7, 2);
	case 31:  return sf::Vector2i(8, 0);
	case 32:  return sf::Vector2i(8, 1);
	case 34:  return sf::Vector2i(8, 2);
	//case 35:  return sf::Vector2i(0, 3); // Dworzec 4
	case 37:  return sf::Vector2i(9, 0);
	case 39:  return sf::Vector2i(9, 1);
	default:
		return sf::Vector2i(-1, -1);
	}
}