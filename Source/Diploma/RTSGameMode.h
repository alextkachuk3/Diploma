#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BVH/BVHTree.h"
#include "PlayerStats.h"
#include "InstancedFoliageActor.h"
#include <Kismet/GameplayStatics.h>
#include "RTSGameMode.generated.h"

UCLASS()
class DIPLOMA_API ARTSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARTSGameMode();
	PlayerStats PlayerOneStats;
	PlayerStats PlayerTwoStats;
	BVHTree* MapTreesBVHTree;
private:
	

	void BeginPlay() override;

	std::vector<FVector2D> GetAllTreesLocations();
	std::vector<FVector2D> TreesLocations;
};
