#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RightMouseClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> WidgetClass;

	UUserWidget* MyWidget;

	UFUNCTION(BlueprintCallable)
		void LeftMouseButtonClickAction();
	UFUNCTION(BlueprintCallable)
		void RightMouseButtonClickAction();

	UFUNCTION(BlueprintCallable)
		void SpawnMine(UPlayerInfo* PlayerInfo);

	UFUNCTION(BlueprintCallable)
		void SpawnLumberjackHut(UPlayerInfo* PlayerInfo);

	UFUNCTION(BlueprintCallable)
		void SpawnForge(UPlayerInfo* PlayerInfo);

	UFUNCTION(BlueprintCallable)
		void SpawnSawmill(UPlayerInfo* PlayerInfo);

	UFUNCTION(BlueprintCallable)
		void SpawnBarrack(UPlayerInfo* PlayerInfo);

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
	bool BuildingInsideBorder(AActor* Actor);
	FBox GetStaticMeshBoundingBox(UWorld* World, const FString& StaticMeshName);
	FVector GetLandscapeMouseCursorLocation();
	const double MinXBorder = -24500.0;
	const double MinYBorder = -16000.0;
	const double MaxXBorder = 16700.0;
	const double MaxYBorder = 23700.0;

	FBox PlayerOneTownHall;
	FBox PlayerTwoTownHall;
};
