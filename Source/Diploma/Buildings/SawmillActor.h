#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "SawmillActor.generated.h"

UCLASS()
class DIPLOMA_API ASawmillActor : public ABuilding
{
	GENERATED_BODY()

public:
	ASawmillActor();
	ASawmillActor(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;
	
};
