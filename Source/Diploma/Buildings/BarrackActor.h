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
	ABarrackActor(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void IncreaseMilitaryPower();

private:	
	void DecreaseMilitaryPower(const int& Count);
	int GetMilitaryPower();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int MilitaryPower;

	const int MaxMilitaryPower = 20;
};
