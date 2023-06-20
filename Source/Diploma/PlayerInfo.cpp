#include "PlayerInfo.h"

void UPlayerInfo::IncreaseLumberCount(const int& Count)
{
	LumberCount += Count;
}

void UPlayerInfo::DecraseLumberCount(const int& Count)
{
	LumberCount -= Count;
	if (LumberCount < 0)
		LumberCount = 0;
}

int UPlayerInfo::GetLumberCount()
{
	return LumberCount;
}

void UPlayerInfo::IncreaseBoardCount(const int& Count)
{
	BoardCount += Count;
}

void UPlayerInfo::DecraseBoardCount(const int& Count)
{
	BoardCount -= Count;
	if (BoardCount < 0)
		BoardCount = 0;
}

int UPlayerInfo::GetBoardCount()
{
	return BoardCount;
}

void UPlayerInfo::IncreaseStoneCount(const int& Count)
{
	StoneCount += Count;
}

void UPlayerInfo::DecraseStoneCount(const int& Count)
{
	StoneCount -= Count;
	if (StoneCount < 0)
		StoneCount = 0;
}

int UPlayerInfo::GetStoneCount()
{
	return StoneCount;
}

void UPlayerInfo::IncreaseIronCount(const int& Count)
{
	IronCount += Count;
}

void UPlayerInfo::DecraseIronCount(const int& Count)
{
	IronCount -= Count;
	if (IronCount < 0)
		IronCount = 0;
}

int UPlayerInfo::GetIronCount()
{
	return IronCount;
}