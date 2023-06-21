#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <algorithm>
#include "PlayerInfo.generated.h"

//class ABuilding;

UCLASS()
class DIPLOMA_API UPlayerInfo : public UObject
{
	GENERATED_BODY()

public:
	UPlayerInfo();

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

	void AddBuilding(AActor* Building);
	void RemoveBuilding(AActor* Building);

	void AddMilitaryBuilding(AActor* Building);
	void RemoveMilitaryBuilding(AActor* Building);

	bool IntersectOtherBuilding(AActor* Building);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int LumberCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int BoardCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int StoneCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int IronCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int WeaponCount;

	std::vector<AActor*> PlayerBuildings;
	std::vector<AActor*> PlayerMilitaryBuildings;
};
