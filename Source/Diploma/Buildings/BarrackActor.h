#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "BarrackActor.generated.h"

UCLASS()
class DIPLOMA_API ABarrackActor : public ABuilding
{
	GENERATED_BODY()

public:
	ABarrackActor();
	virtual void Tick(float DeltaTime) override;
	
};
