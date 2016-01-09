#pragma once
#include "field.h"
#include <list>

std::list<Field*> CreateList_ptrField(Graphics& graphics);
Field* FindField(std::list<Field*> list, const unsigned int ID);