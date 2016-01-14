#include <iostream>
#include <Windows.h>
#include "game.h"


void main()
{
	FreeConsole();
	Game monopoly;
	monopoly.Rungame();
	return;
}

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





	
	