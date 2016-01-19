#pragma once
#include <string>
#include <algorithm>
#include <list>
#include "card.h"
#include "buttontext.h"

class Field : public sf::Drawable, public sf::Transformable
{
	unsigned int area;
	bool showButtons;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states){}

public:
	Field(unsigned int area, bool showButtons = true) : area(area), showButtons(showButtons){}
	virtual ~Field(){}
	unsigned int GetArea(){ return area; }
	bool ShowButtonsOnCard(){ return showButtons; }

	virtual void Action(Player& player) = 0;
	virtual std::vector<ButtonSprite>& ShowGraphics() = 0;
	virtual std::vector<ButtonText>& ShowTexts() = 0;
	virtual void GetOwnerAndPrice(Player*& owner, unsigned int& price, Player* activePlayer) = 0;

	sf::Vector2i ChooseCard(unsigned int area)
	{
		switch (area)
		{
		case 1:	  return sf::Vector2i(2, 0);
		case 3:	  return sf::Vector2i(2, 1);
		case 5:	  return sf::Vector2i(0, 0); // Dworzec 1
		case 6:	  return sf::Vector2i(3, 0);
		case 8:	  return sf::Vector2i(3, 1);
		case 9:	  return sf::Vector2i(3, 2);
		case 11:  return sf::Vector2i(4, 0);
		case 12:  return sf::Vector2i(1, 0); // ELEKTROWNIA
		case 13:  return sf::Vector2i(4, 1);
		case 14:  return sf::Vector2i(4, 2);
		case 15:  return sf::Vector2i(0, 1); // Dworzec 2
		case 16:  return sf::Vector2i(5, 0);
		case 18:  return sf::Vector2i(5, 1);
		case 19:  return sf::Vector2i(5, 2);
		case 21:  return sf::Vector2i(6, 0);
		case 23:  return sf::Vector2i(6, 1);
		case 24:  return sf::Vector2i(6, 2);
		case 25:  return sf::Vector2i(0, 2); // Dworzec 3
		case 26:  return sf::Vector2i(7, 0);
		case 27:  return sf::Vector2i(7, 1);
		case 28:  return sf::Vector2i(1, 1); // WODOCIĄG
		case 29:  return sf::Vector2i(7, 2);
		case 31:  return sf::Vector2i(8, 0);
		case 32:  return sf::Vector2i(8, 1);
		case 34:  return sf::Vector2i(8, 2);
		case 35:  return sf::Vector2i(0, 3); // Dworzec 4
		case 37:  return sf::Vector2i(9, 0);
		case 39:  return sf::Vector2i(9, 1);
		default:
			return sf::Vector2i(-1, -1);
		}
	}
};

class DrawCardField : public Field
{
	std::vector<DrawCard>& cards;
	std::vector<ButtonSprite> graphics;
	std::vector<ButtonText> texts;
	sf::Texture RedCardTexture;
	sf::Font CardFont;
	sf::Texture SpecialTexture;
	bool visibility;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto elem : graphics)
			target.draw(elem.GetSprite());
		for (auto text : texts)
			target.draw(text.GetText());
	}
	
public:
	DrawCardField(std::vector<DrawCard>& cards, Graphics& gameGraphics, sf::Texture& SpecialTexture, const unsigned int& area)
		: 
		cards(cards), 
		RedCardTexture(gameGraphics.GetRedCardTexture()),
		CardFont(gameGraphics.GetCardFont()),
		Field(area, false),
		visibility(false),
		SpecialTexture(SpecialTexture)
	{
		this->RedCardTexture.setSmooth(true);
		this->SpecialTexture.setSmooth(true);

		texts.emplace_back(ButtonText(sf::Text(L"  2016 Marcin Obetkał", this->CardFont, 12), sf::Color::Black, 478, true));

		graphics.emplace_back(this->RedCardTexture, (700 - 450) / 2, (700 - 290) / 2);
		graphics.emplace_back(this->SpecialTexture, (700 - 450) / 2, (700 - 290) / 2);
	}
	bool isVisible(){ return visibility; }
	void SetVisibility(bool status){ visibility = status; }
	DrawCard& GetCard() { return cards.front(); }
	void ShowDescription()
	{
		graphics.pop_back();
		if (!cards.front().cardWasUsed())
			texts.emplace_back(ButtonText(sf::Text(cards.front().GetDescrition(), CardFont, 14), sf::Color::White, 378, true));
		else
		{
			ReloadCardsList();
			texts.emplace_back(ButtonText(sf::Text(cards.front().GetDescrition(), CardFont, 14), sf::Color::White, 378, true));
		}
	}
	void AfterShowDescription()
	{
		graphics.emplace_back(this->SpecialTexture, (700 - 450) / 2, (700 - 290) / 2);
		cards.emplace_back(texts.back().GetText().getString(), true);
		texts.pop_back();
		cards.erase(cards.begin());
	}
	void ReloadCardsList()
	{
		std::random_shuffle(cards.begin(), cards.end());
		for (auto& card : cards)
			card.SetUsed(false);
	}
	void Action(Player& player) override
	{
		//cout << "Karta szansy" << endl;
	}
	void GetOwnerAndPrice(Player*& owner, unsigned int& price, Player* activePlayer) override
	{
		owner = nullptr;
		price = 0;
	}
	std::vector<ButtonSprite>& ShowGraphics() override { return graphics; }
	std::vector<ButtonText>& ShowTexts() override { return texts; }
};

class SpecialField : public Field
{
	SpecialCard card;
	std::vector<ButtonSprite> graphics;
	std::vector<ButtonText> texts;
	sf::Texture CardTexture;
	sf::Font CardFont;
	sf::Texture SpecialTexture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto elem : graphics)
			target.draw(elem.GetSprite());
		for (auto text : texts)
			target.draw(text.GetText());
	}

public:
	SpecialField(const SpecialCard& card, Graphics& gameGraphics, const sf::Texture& SpecialTexture, const unsigned int& area)
		:
		card(card),
		CardTexture(gameGraphics.GetCardTexture()),
		Field(area),
		CardFont(gameGraphics.GetCardFont()),
		SpecialTexture(SpecialTexture)
	{
		this->CardTexture.setSmooth(true);
		this->SpecialTexture.setSmooth(true);
		texts.emplace_back(ButtonText(this->card.Get_title(), sf::Color::Black, 330, true));

		texts.emplace_back(ButtonText(sf::Text(L"Właściciel jednego obiektu użyteczności", CardFont, 14), sf::Color::Black, 370, false));
		texts.emplace_back(ButtonText(sf::Text(L"publicznej pobiera czterokrotną wartość", CardFont, 14), sf::Color::Black, 385, false));
		texts.emplace_back(ButtonText(sf::Text(L"sumy wyrzuconych oczek.", CardFont, 14), sf::Color::Black, 400, false));

		texts.emplace_back(ButtonText(sf::Text(L"Właściciel jednego obiektu użyteczności", CardFont, 14), sf::Color::Black, 430, false));
		texts.emplace_back(ButtonText(sf::Text(L"publicznej pobiera dziesięciokrotną wartość", CardFont, 14), sf::Color::Black, 445, false));
		texts.emplace_back(ButtonText(sf::Text(L"sumy wyrzuconych oczek.", CardFont, 14), sf::Color::Black, 460, false));

		texts.emplace_back(ButtonText(sf::Text(L"Wartość HIPOTECZNA", CardFont, 15), sf::Color::Black, 485, false, -58.0f));
		texts.emplace_back(ButtonText(sf::Text((sf::String)(std::to_string(this->card.Get_mortgage())) + L" zł", CardFont, 15), sf::Color::Black, 485, true, 108.0f));
		texts.emplace_back(ButtonText(sf::Text(L"  2016 Marcin Obetkał", CardFont, 12), sf::Color::Black, 559, true));

		graphics.emplace_back(this->CardTexture, (700 - 290) / 2, 125.0f);
		graphics.emplace_back(this->SpecialTexture, (700 - 220) / 2, 140.0f);
	}
	SpecialCard& GetCard() { return card; }
	void Action(Player& player) override
	{
		if (card.GetOwner() == nullptr)
		{
			card.SetOwner(player);
			player.SpendMoney(card.Get_CardPrice());	
			sf::Vector2i Cords(ChooseCard(this->GetArea()));
			if (Cords.x != -1 && Cords.y != -1)
			{
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetCardStatusOwner(&player);
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetMiniCardArea(this->GetArea());
			}
		}
	}
	void GetOwnerAndPrice(Player*& owner, unsigned int& price, Player* activePlayer) override
	{
		owner = card.GetOwner();
		int meshNumber = activePlayer->GetPawn().GetLastRollDice();
		if (owner)
		{
			int multiplier = -1;
			for (auto& status : owner->GetCardsStatus()[1]->GetVectorCards())
			{
				if (status.GetMiniCardOwner() == owner)
					++multiplier;
			}
			price = meshNumber * 4 + meshNumber*multiplier * 6;
		}
	}
	std::vector<ButtonSprite>& ShowGraphics() override { return graphics; }
	std::vector<ButtonText>& ShowTexts() override { return texts; }
};

class TrainField : public Field
{
	TrainCard card;
	std::vector<ButtonSprite> graphics;
	std::vector<ButtonText> texts;
	sf::Texture CardTexture;
	sf::Font CardFont;
	sf::Texture Train;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto elem : graphics)
			target.draw(elem.GetSprite());
		for (auto text : texts)
			target.draw(text.GetText());
	}

public:
	TrainField(const TrainCard& card, Graphics& gameGraphics, const unsigned int& area)
		:
		card(card),
		CardTexture(gameGraphics.GetCardTexture()),
		Field(area),
		CardFont(gameGraphics.GetCardFont()),
		Train(gameGraphics.GetTrainLogoTexture())
	{
		this->CardTexture.setSmooth(true);
		this->Train.setSmooth(true);
		texts.emplace_back(ButtonText(this->card.Get_title(), sf::Color::Black, 300, true));
		texts.emplace_back(ButtonText(sf::Text(L"CZYNSZ\nWłaściciel 2 dworców pobiera\nWłaściciel 3 dworców pobiera\nWłaściciel 4 dworców pobiera", CardFont, 16), sf::Color::Black, 350, false, -35.0));
		texts.emplace_back(ButtonText(sf::Text(this->card.ShowRents(), CardFont, 16), sf::Color::Black, 350, true, 103.0f));
		texts.emplace_back(ButtonText(sf::Text(L"Wartość HIPOTECZNA", CardFont, 16), sf::Color::Black, 475, false, -55.0f));
		texts.emplace_back(ButtonText(sf::Text((sf::String)(std::to_string(this->card.Get_mortgage())) + L" zł", CardFont, 16), sf::Color::Black, 475, true, 105.0f));
		texts.emplace_back(ButtonText(sf::Text(L"  2016 Marcin Obetkał", CardFont, 12), sf::Color::Black, 559, true));

		graphics.emplace_back(this->CardTexture, (700 - 290) / 2, 125.0f);
		graphics.emplace_back(this->Train, (700 - 195) / 2, 150.0f);
	}
	TrainCard& GetCard() { return card; }
	void Action(Player& player) override
	{
		if (card.GetOwner() == nullptr)
		{
			card.SetOwner(player);
			player.SpendMoney(card.Get_CardPrice());
			sf::Vector2i Cords(ChooseCard(this->GetArea()));
			if (Cords.x != -1 && Cords.y != -1)
			{
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetCardStatusOwner(&player);
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetMiniCardArea(this->GetArea());
			}
		}
	}

	void GetOwnerAndPrice(Player*& owner, unsigned int& price, Player* activePlayer) override
	{
		owner = card.GetOwner();
		price = card.Get_Rent();
		if (owner)
		{
			for (auto& status : owner->GetCardsStatus()[0]->GetVectorCards())
			{
				if (status.GetMiniCardOwner() == owner)
					price *= 2;
			}
			price = price / 2;
		}
	}
	
	std::vector<ButtonSprite>& ShowGraphics() override { return graphics; }
	std::vector<ButtonText>& ShowTexts() override { return texts; }
};

class DeedField : public Field
{
	DeedCard card;
	std::vector<ButtonSprite> graphics;
	std::vector<ButtonText> texts;
	sf::Texture CardTexture;
	sf::Font CardFont;
	sf::VertexArray Color;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto elem : graphics)
			target.draw(elem.GetSprite());
		target.draw(Color);
		for (auto text : texts)
			target.draw(text.GetText());
	}

public:
	DeedField(const DeedCard& card, Graphics& gameGraphics, sf::Color color, const unsigned int& area)
		: 
		card(card), 
		CardTexture(gameGraphics.GetCardTexture()), 
		Field(area), 
		CardFont(gameGraphics.GetCardFont()),
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

		graphics.emplace_back(this->CardTexture, (700 - 290) / 2, 125.0f);
	}
	sf::VertexArray& GetColor(){ return Color; }
	DeedCard& GetCard() { return card; }
	void Action(Player& player) override
	{
		if (card.GetOwner() == nullptr)
		{
			card.SetOwner(player);
			player.SpendMoney(card.Get_landPrice());
			sf::Vector2i Cords(ChooseCard(this->GetArea()));
			if (Cords.x != -1 && Cords.y != -1)
			{
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetCardStatusOwner(&player);
				player.GetCardsStatus()[Cords.x]->GetVectorCards()[Cords.y].SetMiniCardArea(this->GetArea());
			}
		}
	}

	void GetOwnerAndPrice(Player*& owner, unsigned int& price, Player* activePlayer) override
	{
		owner = card.GetOwner();
		price = card.Get_rents().Get_withoutHouse();
	}

	std::vector<ButtonSprite>& ShowGraphics() override { return graphics; }
	std::vector<ButtonText>& ShowTexts() override {	return texts; }
};