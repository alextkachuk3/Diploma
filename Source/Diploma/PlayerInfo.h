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
	void DecreaseLumberCount(const int& Count);
	int GetLumberCount();

	void IncreaseBoardCount(const int& Count);
	void DecreaseBoardCount(const int& Count);
	int GetBoardCount();

	void IncreaseStoneCount(const int& Count);
	void DecreaseStoneCount(const int& Count);
	int GetStoneCount();

	void IncreaseIronCount(const int& Count);
	void DecreaseIronCount(const int& Count);
	int GetIronCount();

	void IncreaseWeaponCount(const int& Count);
	void DecreaseWeaponCount(const int& Count);
	int GetWeaponCount();

	void Reset();

private:
	int LumberCount = 0;
	int BoardCount = 0;
	int StoneCount = 0;
	int IronCount = 0;
	int WeaponCount = 0;

	std::vector<ABuilding*> PlayerBuildings;
	std::vector<ABuilding*> PlayerMilitaryBuildings;
};
