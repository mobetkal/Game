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
	bool active;
	bool doublet;
	int blockMovement;

public:
	Player(const std::string& name, Pawn pawn)
		:
		name(name),
		pawn(pawn),
		money(1500),
		jailCard(false),
		doublet(false),
		activeMovement(false),
		active(false),
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
	bool Money(int value, bool use = true)
	{
		if ((money + value) >= 0)
		{
			if (use)
				money += value;
			return true;
		}
		else
			return false;
	}
	int AccoundStatus()
	{
		return money;
	}
	bool ThrewDoublet()
	{
		return doublet;
	}
	void SetDoublet(bool doublet)
	{
		this->doublet = doublet;
	}
	Pawn& GetPawn()
	{
		return pawn;
	}
	void SetActiveMovement(bool move)
	{
		activeMovement = move;
	}
	bool IsActiveMovement()
	{
		return activeMovement;
	}
	void SetActive(bool active)
	{
		this->active = active;
	}
	bool IsActive()
	{
		return active;
	}
	std::string GetString() const
	{
		return name;
	}
};