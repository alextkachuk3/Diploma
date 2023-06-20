#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "ForgeActor.generated.h"

UCLASS()
class DIPLOMA_API AForgeActor : public ABuilding
{
	GENERATED_BODY()

public:
	AForgeActor();
	AForgeActor(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;
	
};
