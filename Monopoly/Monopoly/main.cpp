//#include <iostream>
//#include <Windows.h>
//#include "game.h"
//
//int main()
//{
//	FreeConsole();
//	Game monopoly;
//	monopoly.Rungame();
//	return 0;
//}

#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;

class Rent
{
	friend class boost::serialization::access;
	unsigned int withoutHouse;
	unsigned int oneHouse;
	unsigned int twoHouses;
	unsigned int threeHouses;
	unsigned int hotel;
	template<class Archive>
	void serialize(Archive & archive, const unsigned int){
		archive & withoutHouse & oneHouse & twoHouses & threeHouses & hotel;
	}

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
};

class Card
{
	friend class boost::serialization::access;
	string title;
	unsigned int landPrice;
	unsigned int mortgage;
	unsigned int ID_Card;

	template<class Archive>
	void serialize(Archive &archive, const unsigned int version)
	{
		archive & title & landPrice & mortgage & ID_Card;
	}
protected:
	Card(const string& title, const unsigned int& landPrice, const unsigned int& mortgage, const unsigned int& ID_Card)
		:
		title(title),
		landPrice(landPrice),
		mortgage(mortgage),
		ID_Card(ID_Card)
	{}
public:
	Card(){}
	~Card(){}
};

class TrainCard : public Card
{
	friend class boost::serialization::access;
	
	template<class Archive>
	void serialize(Archive &archive, const unsigned int version)
	{
		archive & boost::serialization::base_object<Card>(*this);
	}

public:
	TrainCard(){}
	TrainCard(const string& title, unsigned int landPrice, unsigned int mortgage, unsigned int ID_Card)
		:
		Card(title, landPrice, mortgage, ID_Card)
	{}
};

class SpecialCard : public Card
{
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &archive, const unsigned int version)
	{
		archive & boost::serialization::base_object<Card>(*this);
	}

public:
	SpecialCard(){}
	SpecialCard(const string& title, unsigned int landPrice, unsigned int mortgage, unsigned int ID_Card)
		:
		Card(title, landPrice, mortgage, ID_Card)
	{}
};

class DeedCard : public Card
{
	friend class boost::serialization::access;
	Rent rents;
	unsigned int housePrice;
	unsigned int hotelPrice;

	template<class Archive>
	void serialize(Archive &archive, const unsigned int version)
	{
		archive & boost::serialization::base_object<Card>(*this);
		archive & rents & housePrice & hotelPrice;
	}

public:
	DeedCard(){}
	DeedCard(const string& title, const Rent& rents, const unsigned int& landPrice, const unsigned int& housePrice, const unsigned int& hotelPrice, const unsigned int& mortgage, const unsigned int& ID_Card)
		:
		Card(title, landPrice, mortgage, ID_Card),
		rents(rents),
		housePrice(housePrice),
		hotelPrice(hotelPrice)
	{}
};

void Save(const Card &card, const char* filename){
	std::ofstream ofs(filename, ios::app | ios::out);
	boost::archive::text_oarchive bin_oa(ofs);
	bin_oa << card;
}

void Restore(Card &card, const char* filename)
{
	std::ifstream ifs(filename, ios::in);
	boost::archive::text_iarchive bin_ia(ifs);
	bin_ia >> card;
}

int main()
{
	Card* test = new DeedCard(
		"Ulica konopacka", 
		Rent(2, 10, 30, 90, 160), 
		60, 50, 50, 30, 2
		);

	//DeedCard original_card2("Ulica ADGASGASG", 2, 10, 30, 90, 160, 60, 50, 50, 30);
	std::string filename("test_boost.foo");

	Save(*test, filename.c_str());
	//Save(original_card2, filename.c_str());
	
	Card new_card;
	Card new_card2;
	Restore(new_card, filename.c_str());
	//Restore(new_card2, filename.c_str());

	system("pause");
}