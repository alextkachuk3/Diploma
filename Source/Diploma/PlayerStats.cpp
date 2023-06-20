#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
}

PlayerStats::~PlayerStats()
{
}

void PlayerStats::IncreaseLumberCount(const int& Count)
{
	LumberCount += Count;
}

void PlayerStats::DecraseLumberCount(const int& Count)
{
	LumberCount -= Count;
	if (LumberCount < 0)
		LumberCount = 0;
}

int PlayerStats::GetLumberCount()
{
	return LumberCount;
}

void PlayerStats::IncreaseBoardCount(const int& Count)
{
	BoardCount += Count;
}

void PlayerStats::DecraseBoardCount(const int& Count)
{
	BoardCount -= Count;
	if (BoardCount < 0)
		BoardCount = 0;
}

int PlayerStats::GetBoardCount()
{
	return BoardCount;
}

void PlayerStats::IncreaseStoneCount(const int& Count)
{
	StoneCount += Count;
}

void PlayerStats::DecraseStoneCount(const int& Count)
{
	StoneCount -= Count;
	if (StoneCount < 0)
		StoneCount = 0;
}

int PlayerStats::GetStoneCount()
{
	return StoneCount;
}

void PlayerStats::IncreaseIronCount(const int& Count)
{
	IronCount += Count;
}

void PlayerStats::DecraseIronCount(const int& Count)
{
	IronCount -= Count;
	if (IronCount < 0)
		IronCount = 0;
}

int PlayerStats::GetIronCount()
{
	return IronCount;
}
