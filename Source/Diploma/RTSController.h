#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "InstancedFoliageActor.h"
#include "Buildings/Building.h"
#include "RTSGameMode.h"
#include <Engine/StaticMeshActor.h>
#include "Buildings/BarrackActor.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> OwnBarrackWidgetClass;

	UUserWidget* OwnBarrackWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> EnemyBarrackWidgetClass;

	UUserWidget* EnemyBarrackWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> EnemyTownhallWidgetClass;

	UUserWidget* EnemyTownhallWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UUserWidget> VictoryWidgetClass;

	UUserWidget* VictoryWidget;

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

	UFUNCTION(BlueprintCallable)
		int GetAttackCount(ABarrackActor* BarrackActor, UPlayerInfo* EnemyInfo);
	UFUNCTION(BlueprintCallable)
		int GetTownhallAttackCount(AStaticMeshActor* StaticMeshActor, UPlayerInfo* EnemyInfo);
	UFUNCTION(BlueprintCallable)
		void AttackTownhall(AStaticMeshActor* StaticMeshActor, UPlayerInfo* EnemyInfo);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AStaticMeshActor* PlayerOneTownHallStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		AStaticMeshActor* PlayerTwoTownHallStaticMesh;

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
	bool BuildingCanBePlaced();
	bool BuildingInsideBorder(AActor* Actor);
	AStaticMeshActor* GetStaticMesh(UWorld* World, const FString& StaticMeshName);
	FVector GetLandscapeMouseCursorLocation();
	ABarrackActor* GetClickedBarrack(UPlayerInfo* PlayerInfo);
	const double MinXBorder = -24500.0;
	const double MinYBorder = -16000.0;
	const double MaxXBorder = 16700.0;
	const double MaxYBorder = 23700.0;
	FBox PlayerOneTownHall;
	FBox PlayerTwoTownHall;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ABarrackActor* LastSelectedOwnBarrackActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ABarrackActor* LastSelectedEnemyBarrackActor;
};
