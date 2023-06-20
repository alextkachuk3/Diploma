#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"

class DIPLOMA_API PlayerStats
{
public:
	PlayerStats();
	~PlayerStats();

	void IncreaseLumberCount(const int& Count);
	void DecraseLumberCount(const int& Count);
	int GetLumberCount();

	void IncreaseBoardCount(const int& Count);
	void DecraseBoardCount(const int& Count);
	int GetBoardCount();

	void IncreaseStoneCount(const int& Count);
	void DecraseStoneCount(const int& Count);
	int GetStoneCount();

	void IncreaseIronCount(const int& Count);
	void DecraseIronCount(const int& Count);
	int GetIronCount();

private:
	int LumberCount = 0;
	int BoardCount = 0;
	int StoneCount = 0;
	int IronCount = 0;

	std::vector<ABuilding*> PlayerBuildings;
	std::vector<ABuilding*> PlayerMilitaryBuildings;
};
