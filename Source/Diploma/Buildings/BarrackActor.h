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
	int GetMilitaryPower();

	UFUNCTION(BlueprintCallable)
		void IncreaseMilitaryPower();

	const static int BoardPrice = 4;
	const static int StonePrice = 8;

private:	
	void DecreaseMilitaryPower(const int& Count);
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int MilitaryPower;

	const int MaxMilitaryPower = 20;
};
