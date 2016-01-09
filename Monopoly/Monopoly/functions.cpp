//#include <SFML\Graphics.hpp>
//#include <list>
//#include "field.h"
//
//using namespace sf;
//
//Field* FindField(std::list<Field*> list, const unsigned int ID)
//{
//	auto elem = list.begin();
//	auto end = list.end();
//	while (elem != end)
//	{
//		if ((*elem)->GetArea() == ID)
//			return *elem;
//		++elem;
//	}
//	return nullptr;
//}
//
//std::list<Field*> CreateList_ptrField(Graphics& graphics)
//{
//	Font& CardFont = graphics.GetCardFont();
//	Texture DeedCardTexture = graphics.GetDeedCardTexture();
//
//	std::list<Field*> fields;
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA KONOPACKA", CardFont, Rent(2, 10, 30, 90, 160), 60, 50, 50, 30), DeedCardTexture, Color(78, 61, 113), 1
//		));
//	//// kasa społeczna 2
//
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA STALOWA", CardFont, Rent(4, 20, 60, 180, 320), 60, 50, 50, 30), DeedCardTexture, Color(78, 61, 113), 3
//		));
//	////fields.emplace_back(4); -200ZŁ 4
//	///*fields.emplace_back(new TrainField(
//	//	SpecialCard("Dworzec Zachodni", 200, 100), 25, 5
//	//	));*/
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA RADZYMIŃSKA", CardFont, Rent(6, 30, 90, 270, 400), 100, 50, 50, 50), DeedCardTexture, Color(178, 194, 228), 6
//		));
//
//	//// karta szansy 7
//
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA JAGIELLOŃSKA", CardFont, Rent(6, 30, 90, 270, 400), 100, 50, 50, 50), DeedCardTexture, Color(178, 194, 228), 8
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA TARGOWA", CardFont, Rent(8, 40, 100, 300, 450), 120, 50, 50, 60), DeedCardTexture, Color(178, 194, 228), 9
//		));
//	//10 NIC
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA PŁOWIECKA", CardFont, Rent(10, 50, 150, 450, 625), 140, 100, 100, 70), DeedCardTexture, Color(177, 50, 95), 11
//		));
//	// 12 ELEKTROWNIA
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA MARSA", CardFont, Rent(10, 50, 150, 450, 625), 140, 100, 100, 70), DeedCardTexture, Color(177, 50, 95), 13
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA GROCHOWSKA", CardFont, Rent(12, 60, 180, 500, 700), 160, 100, 100, 80), DeedCardTexture, Color(177, 50, 95), 14
//		));
//	//DWORZEC 15
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA OBOZOWA", CardFont, Rent(14, 70, 200, 550, 750), 180, 100, 100, 90), DeedCardTexture, Color(243, 141, 77), 16
//		));
//	//KASA SPOŁECZNA 17
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA GÓRCZEWSKA", CardFont, Rent(14, 70, 200, 550, 750), 180, 100, 100, 90), DeedCardTexture, Color(243, 141, 77), 18
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA WOLSKA", CardFont, Rent(16, 80, 220, 600, 800), 200, 100, 100, 100), DeedCardTexture, Color(243, 141, 77), 19
//		));
//	//20 NIC
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA MICKIEWICZA", CardFont, Rent(18, 90, 250, 700, 875), 220, 150, 150, 110), DeedCardTexture, Color(239, 59, 58), 21
//		));
//	//KARTA SZANSY 22
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA SŁOWACKIEGO", CardFont, Rent(18, 90, 250, 700, 875), 220, 150, 150, 110), DeedCardTexture, Color(239, 59, 58), 23
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA WILSONA", CardFont, Rent(20, 100, 300, 750, 925), 240, 150, 150, 120), DeedCardTexture, Color(239, 59, 58), 24
//		));
//	// DWORZEC 25
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA ŚWIĘTOKRZYSKA", CardFont, Rent(22, 110, 330, 800, 975), 260, 150, 150, 130), DeedCardTexture, Color(237, 247, 140), 26
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"KRAKOWSKIE PRZEDMIEŚCIE", CardFont, Rent(22, 110, 330, 800, 975), 260, 150, 150, 130), DeedCardTexture, Color(237, 247, 140), 27
//		));
//	//WODOCIAG 28
//	fields.emplace_back(new DeedField(
//		DeedCard(L"NOWY ŚWIAT", CardFont, Rent(24, 120, 360, 850, 1025), 280, 150, 150, 140), DeedCardTexture, Color(237, 247, 140), 29
//		));
//	//GO TO JAIL! 30
//	fields.emplace_back(new DeedField(
//		DeedCard(L"PLAC TRZECH KRZYŻY", CardFont, Rent(26, 130, 390, 900, 1100), 300, 200, 200, 150), DeedCardTexture, Color(83, 148, 114), 31
//		));
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ULICA MARSZAŁKOWSKA", CardFont, Rent(26, 130, 390, 900, 1100), 300, 200, 200, 150), DeedCardTexture, Color(83, 148, 114), 32
//		));
//	//KASA SPOŁECZNA 33
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ALEJE JEROZOLIMSKIE", CardFont, Rent(28, 150, 450, 1000, 1200), 320, 200, 200, 160), DeedCardTexture, Color(83, 148, 114), 34
//		));
//	//DWORZEC 35
//	//SZANSA 36
//	fields.emplace_back(new DeedField(
//		DeedCard(L"BELWEDERSKA", CardFont, Rent(35, 175, 500, 1100, 1300), 350, 200, 200, 175), DeedCardTexture, Color(56, 79, 146), 37
//		));
//	//PODATEK -100ZŁ 38
//	fields.emplace_back(new DeedField(
//		DeedCard(L"ALEJE UJAZDOWSKIE", CardFont, Rent(50, 200, 600, 1400, 1700), 400, 200, 200, 200), DeedCardTexture, Color(56, 79, 146), 39
//		));
//	//FindField(fields, 6)->Action();
//	return fields;
//}