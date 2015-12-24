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
	Player(const std::string& name, Pawn pawn, bool activeMovement = false)
		:
		name(name),
		pawn(pawn),
		money(1500),
		jailCard(false),
		activeMovement(activeMovement),
		blockMovement(0)
	{
		
	};
	void operator--()
	{
		if (blockMovement)
			blockMovement -= 1;
	}
	int IsBlocked()
	{
		return blockMovement;
	}
	void SetBlock(int rounds)
	{
		blockMovement = rounds;
	}
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