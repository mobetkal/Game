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

class Card
{
	friend class boost::serialization::access;
	string title;
	vector<int> rents;
	int housePrice;
	int hotelPrice;
	int landPrice;
	int deposit;

	template<class Archive>
	void serialize(Archive &archive, const unsigned int version)
	{
		archive & title & rents & landPrice & housePrice & hotelPrice & deposit;
	}

public:
	Card(){}
	Card(const string& title, int rent_0, int rent_1, int rent_2, int rent_3, int rent_4, int landPrice, int housePrice, int hotelPrice, int deposit)
		:
		title(title),
		landPrice(landPrice),
		housePrice(housePrice),
		hotelPrice(hotelPrice),
		deposit(deposit)
	{
		rents.emplace_back(rent_0);
		rents.emplace_back(rent_1);
		rents.emplace_back(rent_2);
		rents.emplace_back(rent_3);
		rents.emplace_back(rent_4);
	}
};

void Save(const Card &card, const char* filename){
	std::ofstream ofs(filename, ios::binary);
	boost::archive::text_oarchive bin_oa(ofs);
	bin_oa << card;
}

void Restore(Card &card, const char* filename)
{
	std::ifstream ifs(filename, ios::binary);
	boost::archive::text_iarchive bin_ia(ifs);
	bin_ia >> card;
}

int main()
{
	Card original_card("Ulica konopacka", 2, 10, 30, 90, 160, 60, 50, 50, 30);

	std::string filename("test_boost.foo");

	Save(original_card, filename.c_str());

	Card new_card;

	Restore(new_card, filename.c_str());
	system("pause");
}

//#include <iostream>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <vector>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
//class Vector {
//public:
//	float x;
//	float y;
//	Vector(float x, float y) : x(x), y(y) {}
//	Vector() {}
//	template<class Archive>
//	void serialize(Archive & ar, const unsigned int version) 
//	{
//		ar & x;
//		ar & y;
//	}
//};
//
//void main()
//{
//	std::string filename = "archive.txt";
//	// zapisz obiekt do archiwum tekstowego
//	Vector v1(1.0f, 2.0f);
//	std::ofstream ofs(filename);
//	boost::archive::text_oarchive oa(ofs);
//	oa << v1;
//	// odczytaj obiekt z archiwum tekstowego
//	Vector v2;
//	std::ifstream ifs(filename);
//	boost::archive::text_iarchive ia(ifs);
//	ia >> v2;
//
//	system("pause");
//}