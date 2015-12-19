#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>

class Pawn
{
	sf::Texture texturePawn;
	sf::Sprite pawn;
	std::vector<std::pair<float, float>> possition;
	int area;
public:
	Pawn(sf::Texture& texturePawn, int area = 0)
		: 
		texturePawn(texturePawn),
		area(area)
	{
		texturePawn.setSmooth(true);
		pawn.setTexture(texturePawn);
		LoadPossitons();
		pawn.setPosition(possition[area].first, possition[area].second);
	};
	void LoadPossitons()
	{
		possition.emplace_back(std::make_pair(620.0f, 620.0f)); //START
		possition.emplace_back(std::make_pair(550.5f, 633.0f));
		possition.emplace_back(std::make_pair(494.0f, 633.0f));
		possition.emplace_back(std::make_pair(437.0f, 633.0f));
		possition.emplace_back(std::make_pair(380.5f, 633.0f));
		possition.emplace_back(std::make_pair(324.0f, 633.0f));
		possition.emplace_back(std::make_pair(267.0f, 633.0f));
		possition.emplace_back(std::make_pair(211.0f, 633.0f));
		possition.emplace_back(std::make_pair(154.0f, 633.0f));
		possition.emplace_back(std::make_pair(97.0f, 633.0f));
		possition.emplace_back(std::make_pair(154.0f, 633.0f)); // LEFT BOTTOM SITE -> JAIL => Dodaj Mnie! :P
		possition.emplace_back(std::make_pair(15.0f, 551.0f));
		possition.emplace_back(std::make_pair(15.0f, 494.0f));
		possition.emplace_back(std::make_pair(15.0f, 437.0f));
		possition.emplace_back(std::make_pair(15.0f, 380.0f));
		possition.emplace_back(std::make_pair(15.0f, 323.0f));
		possition.emplace_back(std::make_pair(15.0f, 267.0f));
		possition.emplace_back(std::make_pair(15.0f, 210.0f));
		possition.emplace_back(std::make_pair(15.0f, 153.0f));
		possition.emplace_back(std::make_pair(15.0f, 96.0f));
		possition.emplace_back(std::make_pair(23.0f, 24.0f)); // LEFT TOP SITE
		possition.emplace_back(std::make_pair(97.0f, 15.0f));
		possition.emplace_back(std::make_pair(154.0f, 15.0f));
		possition.emplace_back(std::make_pair(210.5f, 15.0f));
		possition.emplace_back(std::make_pair(267.0f, 15.0f));
		possition.emplace_back(std::make_pair(324.0f, 15.0f));
		possition.emplace_back(std::make_pair(380.5f, 15.0f));
		possition.emplace_back(std::make_pair(437.5f, 15.0f));
		possition.emplace_back(std::make_pair(494.0f, 15.0f));
		possition.emplace_back(std::make_pair(550.0f, 15.0f));
		possition.emplace_back(std::make_pair(623.0f, 24.0f)); // RIGHT TOP SITE
		possition.emplace_back(std::make_pair(633.0f, 96.0f));
		possition.emplace_back(std::make_pair(633.0f, 153.0f));
		possition.emplace_back(std::make_pair(633.0f, 210.0f));
		possition.emplace_back(std::make_pair(633.0f, 267.0f));
		possition.emplace_back(std::make_pair(633.0f, 324.0f));
		possition.emplace_back(std::make_pair(633.0f, 380.0f));
		possition.emplace_back(std::make_pair(633.0f, 437.0f));
		possition.emplace_back(std::make_pair(633.0f, 494.0f));
		possition.emplace_back(std::make_pair(633.0f, 551.0f)); 
	}
	sf::Sprite& GetSprite()
	{
		return pawn;
	}
	sf::Texture& GetTexture()
	{
		return texturePawn;
	}
	std::pair<float, float>& GetPossition(int area)
	{
		return possition[area];
	}
	int GetArea()
	{
		return area;
	}
	void move(int meshNumber)
	{
		for (int i = 1; i <= meshNumber; ++i)
		{
			if (area + i < 40)
				pawn.setPosition(possition[i + area].first, possition[i + area].second);
			else
			{
				for (int j = 0; j <= (meshNumber - i); ++j)
				{
					pawn.setPosition(possition[j].first, possition[j].second);
					area = j;
				}
				//DODANIE KASY
				return;
			}
		}
		Sleep(500);
		area = area + meshNumber;
	}
};