#include <iostream>
#include <Windows.h>
#include "game.h"

int main()
{
	FreeConsole();
	Game monopoly;
	monopoly.Rungame();
	return 0;
}