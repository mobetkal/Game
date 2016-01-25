#include <iostream>
#include <Windows.h>
#include "game.h"
#include "DetectMemoryLeaks.h"

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
