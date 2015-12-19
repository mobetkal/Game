#pragma once
#include <iostream>
#include "pawn.h"

class Player
{
	const std::string name;
	Pawn pawn;
	int money;
	bool jailCard;
	bool activeMovement;
	int blockMovement;

public:
	Player(const std::string& name, Pawn pawn, int players, bool activeMovement = false, bool jailCard = false)
		:
		name(name),
		pawn(pawn),
		money((int)(2000 / players)),
		jailCard(jailCard),
		activeMovement(activeMovement)
	{
		
	};
	Pawn& GetPawn()
	{
		return pawn;
	}
	void SetActiveMovement(bool move)
	{
		activeMovement = move;
	}
	bool IsActive()
	{
		return activeMovement;
	}
	std::string GetString() const
	{
		return name;
	}
};