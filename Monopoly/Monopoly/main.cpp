#include <iostream>
#include <Windows.h>
//#include <list>
#include "game.h"
//#include "field.h"

void main()
{
	FreeConsole();
	Game monopoly;
	monopoly.Rungame();
	return;
}
//
//#include <SFML/Window.hpp>
//#include <Windows.h>
//
//using namespace sf;
//using namespace std;
//
//int main()
//{
//	FreeConsole();
//	sf::Window window(sf::VideoMode(900, 650, 32), "Komunikator by Kacu");
//	window.setPosition(Vector2i(100, 10));
//	window.setKeyRepeatEnabled(true);
//	window.setVerticalSyncEnabled(true);
//	window.setFramerateLimit(60);
//
//	while (window.isOpen())
//	{
//		// check all the window's events that were triggered since the last iteration of the loop
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// "close requested" event: we close the window
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//	}
//
//	return 0;
//}


//void Save(const list<Field*>& list, const char* filename){
//	std::ofstream ofs(filename, ios::out);
//	boost::archive::text_oarchive bin_oa(ofs);
//	bin_oa << list;
//}

//void Restore(const list<Field*>& list, const char* filename)
//{
//	std::ifstream ifs(filename, ios::in);
//	boost::archive::text_iarchive bin_ia(ifs);
//	bin_ia >> list;
//}





	
	