#pragma once
#include <random>

class Dice
{
	std::random_device random;
	std::vector<sf::Texture> meshNumbers;
	int beginValue, endValue;
	bool visible;
	sf::Sprite dice;
public:
	Dice(std::vector<sf::Texture>& meshNumbers, float x, float y, int beginValue = 1, int endValue = 6)
		:
		meshNumbers(meshNumbers),
		beginValue(beginValue),
		endValue(endValue),
		visible(true)
	{
		dice.setTexture(SetTexture(RollDice()));
		dice.setPosition(x, y);
	};
	Dice(int beginValue, int endValue)
		:
		beginValue(beginValue),
		endValue(endValue),
		visible(false)
	{};
	int RollDice()
	{
		std::default_random_engine engine(random());
		std::uniform_int_distribution<int> uniform_dist(beginValue, endValue);
		int meshNumber = uniform_dist(engine);
		if (visible)
			dice.setTexture(SetTexture(meshNumber));
		return meshNumber;
	}
	sf::Texture& SetTexture(int number)
	{
		meshNumbers[number - 1].setSmooth(true);
		return meshNumbers[number - 1];
	}
	sf::Sprite& GetSprite(){ return dice; }
};