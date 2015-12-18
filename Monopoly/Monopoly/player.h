#pragma once
#include <iostream>
#include "pawn.h"

class Player
{
	const std::string name;
	Pawn pawn;
	int money;
	bool jailCard;

public:
	Player(const std::string& name, Pawn pawn, int players, bool jailCard = false)
		:
		name(name),
		pawn(pawn),
		money((int)(2000 / players)),
		jailCard(jailCard)
	{
		
	};
	Pawn& GetPawn()
	{
		return pawn;
	}
};