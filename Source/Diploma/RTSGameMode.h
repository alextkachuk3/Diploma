#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameMode.generated.h"

UCLASS()
class DIPLOMA_API ARTSGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	int WoodCount;
	int BoardsCount;
	int StoneCount;
	int IronCount;
	int SwordCount;

public:
	ARTSGameMode();	
};
