#include <iostream>
#include <Windows.h>
#include "game.h"

void MemoryLeaks()
{
	Game monopoly;
	monopoly.Rungame();
}

void main()
{
	FreeConsole();
	MemoryLeaks();
	_CrtDumpMemoryLeaks();
	return;
}
