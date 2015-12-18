#pragma once
#include <random>

class Dice
{
	std::random_device random;
	std::vector<sf::Texture> meshNumbers;
	sf::Sprite dice;
public:
	Dice(std::vector<sf::Texture>& meshNumbers, float x, float y)
		:
		meshNumbers(meshNumbers)
	{
		dice.setTexture(SetTexture(RollDice()));
		dice.setPosition(x, y);
	};
	int RollDice()
	{
		std::default_random_engine engine(random());
		std::uniform_int_distribution<int> uniform_dist(1, 6);
		int meshNumber = uniform_dist(engine);
		dice.setTexture(SetTexture(meshNumber));
		return meshNumber;
	}
	sf::Texture& SetTexture(int number)
	{
		meshNumbers[number - 1].setSmooth(true);
		return meshNumbers[number - 1];
	}
	sf::Sprite& GetSprite()
	{
		return dice;
	}
};