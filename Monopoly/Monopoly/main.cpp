#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "game.h"

int main()
{
	FreeConsole();
	Game monopoly;
	monopoly.rungame();
	return 0;
}