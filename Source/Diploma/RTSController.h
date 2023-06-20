#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InstancedFoliageActor.h"
#include "Buildings/Building.h"
#include "RTSGameMode.h"
#include "RTSController.generated.h"


UCLASS()
class DIPLOMA_API ARTSController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LeftMouseClickAction;

	UFUNCTION(BlueprintCallable)
		void OnInputStarted();

	UFUNCTION(BlueprintCallable)
		void SpawnMine();

	UFUNCTION(BlueprintCallable)
		void SpawnLumberjackHut();

	UFUNCTION(BlueprintCallable)
		void SpawnForge();

	UFUNCTION(BlueprintCallable)
		void SpawnSawmill();

	UFUNCTION(BlueprintCallable)
		void SpawnBarrack();

	void SpawnBuilding(const FString& BuildingName, const FVector& Scale);

	void SpawnPlayerBuilding(const FString& BuildingName, const FVector& Scale, UPlayerInfo* PlayerInfo);

	UFUNCTION()
		AActor* SpawnActorByName(UWorld* World, const FString& ActorClassName, const FVector& Location, const FRotator& Rotation);

protected:
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay();

private:
	bool BuildingMode;
	ABuilding* ControlledBuilding;
	BoundingVolumeAABB ConrolledBuildingAABB;
	ARTSGameMode* RTSGameMode;
	BoundingVolumeAABB GetActorCornerLocations(AActor* Actor);
};
