#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "LumberjackHutActor.generated.h"

UCLASS()
class DIPLOMA_API ALumberjackHutActor : public ABuilding
{
	GENERATED_BODY()

public:
	ALumberjackHutActor();
	ALumberjackHutActor(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;
	
	const static int BoardPrice = 5;
	const static int StonePrice = 1;
};
