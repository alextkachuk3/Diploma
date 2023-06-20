#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerInfo.generated.h"

class ABuilding;

UCLASS()
class DIPLOMA_API UPlayerInfo : public UObject
{
	GENERATED_BODY()

public:
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