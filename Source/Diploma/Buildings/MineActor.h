#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "MineActor.generated.h"

UCLASS()
class DIPLOMA_API AMineActor : public ABuilding
{
	GENERATED_BODY()

public:
	AMineActor();
	AMineActor(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;

private:
	
	
};
