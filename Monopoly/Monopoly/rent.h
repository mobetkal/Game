#pragma once
#include <string>

class Rent
{
	unsigned int withoutHouse;
	unsigned int oneHouse;
	unsigned int twoHouses;
	unsigned int threeHouses;
	unsigned int hotel;

public:
	Rent(){}
	Rent(const unsigned int& _woutH, const unsigned int& _oneH, const unsigned int& _twoH, const unsigned int& _threeH, const unsigned int& _H)
		:
		withoutHouse(_woutH),
		oneHouse(_oneH),
		twoHouses(_twoH),
		threeHouses(_threeH),
		hotel(_H)
	{}
	sf::String ShowRents()
	{
		return (L"zł\n" + (sf::String)std::to_string(withoutHouse) + "\n" + (sf::String)std::to_string(oneHouse) + "\n" + (sf::String)std::to_string(twoHouses) + "\n" + (sf::String)std::to_string(threeHouses) + "\n" + (sf::String)std::to_string(hotel));
	}
	unsigned int Get_withoutHouse(){ return withoutHouse; }
	unsigned int Get_oneHouse(){ return	oneHouse; }
	unsigned int Get_twoHouses(){ return twoHouses; }
	unsigned int Get_threeHouses(){ return threeHouses; }
	unsigned int Get_hotel(){ return hotel; }
};