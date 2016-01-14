#pragma once
#include <SFML\Graphics.hpp>
class Player;

class MiniCard
{
	sf::VertexArray VertCard;
	sf::Color Color;
	sf::Texture Texture;
	float x;
	float y;
	Player* owner;
	int area;

public:
	sf::VertexArray& GetVertCard(){ return VertCard; }
	sf::Texture& GetMiniCardTexture() { return Texture; }
	Player* GetMiniCardOwner(){ return owner; }
	bool GetBusy()
	{ 
		if (owner)
			return true;
		else
			return false;
	}
	int GetMiniCardArea(){ return area; }
	void SetMiniCardArea(unsigned int newArea){ area = newArea; }
	MiniCard(const sf::Texture& Texture, const sf::Color& Color, const float& x, const float& y, Player* player = nullptr)
		:
		VertCard(sf::Quads, 4),
		Color(Color),
		Texture(Texture),
		x(x),
		y(y),
		area(-1),
		owner(player)
	{
		VertCard[0].position = sf::Vector2f(x, y);				//left-top
		VertCard[1].position = sf::Vector2f(x + 24, y);			//right-top
		VertCard[2].position = sf::Vector2f(x + 24, y + 36);	//right-bottom
		VertCard[3].position = sf::Vector2f(x, y + 36);			//left-bottom
		SetCardStatusOwner(player);
	}
	void SetCardStatusOwner(Player* owner)
	{
		this->owner = owner;
		if (owner)
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