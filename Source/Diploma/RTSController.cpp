#include "RTSController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Engine/ObjectLibrary.h>
#include "EngineUtils.h"
#include "Engine/StaticMesh.h"
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "RTSGameMode.h"
#include "Buildings/BarrackActor.h"
#include "Buildings/MineActor.h"
#include "Buildings/LumberjackHutActor.h"
#include "Buildings/ForgeActor.h"
#include "Buildings/SawmillActor.h"

ARTSController::ARTSController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	ControlledBuilding = nullptr;
	BuildingMode = false;
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	RTSGameMode = Cast<ARTSGameMode>(GetWorld()->GetAuthGameMode());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ARTSController::LeftMouseButtonClickAction);
		EnhancedInputComponent->BindAction(RightMouseClickAction, ETriggerEvent::Triggered, this, &ARTSController::RightMouseButtonClickAction);
	}
}

void ARTSController::Tick(float DeltaTime)
{
	if (BuildingMode && ControlledBuilding)
	{
		ControlledBuilding->SetActorLocation(GetLandscapeMouseCursorLocation());
		ConrolledBuildingAABB = GetActorCornerLocations(ControlledBuilding);
	}
}

AStaticMeshActor* ARTSController::GetStaticMesh(UWorld* World, const FString& StaticMeshName)
{
	FBox BoundingBox(ForceInitToZero);

	for (TActorIterator<AStaticMeshActor> ActorItr(World); ActorItr; ++ActorItr)
	{
		AStaticMeshActor* StaticMeshActor = *ActorItr;
		if (StaticMeshActor && StaticMeshActor->GetStaticMeshComponent())
		{
			if (StaticMeshActor->GetActorLabel() == StaticMeshName)
			{
				return StaticMeshActor;
			}
		}
	}
	return nullptr;
}

FVector ARTSController::GetLandscapeMouseCursorLocation()
{
	FVector2D CursorPosition;
	GetMousePosition(CursorPosition.X, CursorPosition.Y);
	FVector WorldLocation, WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, CursorPosition, WorldLocation, WorldDirection);
	FHitResult HitResult;
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldStatic;
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 50000, TraceChannel);
	return HitResult.Location;
}

ABarrackActor* ARTSController::GetClickedBarrack(UPlayerInfo* PlayerInfo)
{
	return Cast<ABarrackActor>(PlayerInfo->ClickedMilitaryBuilding(GetLandscapeMouseCursorLocation()));
}

void ARTSController::BeginPlay()
{
	Super::BeginPlay();

	PlayerOneTownHallStaticMesh = GetStaticMesh(GetWorld(), TEXT("TawnHallModel1"));
	PlayerTwoTownHallStaticMesh = GetStaticMesh(GetWorld(), TEXT("TawnHallModel2"));

	RTSGameMode->PlayerOneInfo->AddMilitaryBuilding(PlayerOneTownHallStaticMesh);
	RTSGameMode->PlayerTwoInfo->AddMilitaryBuilding(PlayerTwoTownHallStaticMesh);

	PlayerOneTownHall = PlayerOneTownHallStaticMesh->GetComponentsBoundingBox(true);
	PlayerTwoTownHall = PlayerTwoTownHallStaticMesh->GetComponentsBoundingBox(true);
}

BoundingVolumeAABB ARTSController::GetActorCornerLocations(AActor* Actor)
{
	FBox BB = Actor->GetComponentsBoundingBox(true);
	return BoundingVolumeAABB(BB.Min.X, BB.Min.Y, BB.Max.X, BB.Max.Y);
}

bool ARTSController::BuildingCanBePlaced()
{
	return BuildingMode &&
		!RTSGameMode->MapTreesBVHTree->Intersects(ConrolledBuildingAABB) &&
		BuildingInsideBorder(ControlledBuilding) &&
		!RTSGameMode->PlayerOneInfo->IntersectOtherBuilding(ControlledBuilding) &&
		!PlayerOneTownHall.Intersect(ControlledBuilding->GetComponentsBoundingBox(true)) &&
		!PlayerTwoTownHall.Intersect(ControlledBuilding->GetComponentsBoundingBox(true)) &&
		RTSGameMode->PlayerOneInfo->InsideMilitaryBorder(ControlledBuilding);
}

bool ARTSController::BuildingInsideBorder(AActor* Actor)
{
	FBox BB = Actor->GetComponentsBoundingBox(true);
	return BB.Min.X > MinXBorder && BB.Min.Y > MinYBorder && BB.Max.X < MaxXBorder && BB.Max.Y < MaxYBorder;
}

void ARTSController::LeftMouseButtonClickAction()
{
	if (BuildingCanBePlaced())
	{
		if (Cast<ABarrackActor>(ControlledBuilding))
		{
			RTSGameMode->PlayerOneInfo->AddMilitaryBuilding(ControlledBuilding);
		}
		else
		{
			RTSGameMode->PlayerOneInfo->AddBuilding(ControlledBuilding);
		}

		BuildingMode = false;
	}
}

void ARTSController::RightMouseButtonClickAction()
{
	if (BuildingMode)
	{
		if (GetWorld()->ContainsActor(ControlledBuilding))
		{
			GetWorld()->DestroyActor(ControlledBuilding, true, true);
		}
		BuildingMode = false;
	}
	else
	{
		if (PlayerOneTownHall.IsInside(GetLandscapeMouseCursorLocation()))
		{
			MyWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
			if (MyWidget)
			{
				MyWidget->AddToViewport();
			}
		}
		else if (PlayerTwoTownHall.IsInside(GetLandscapeMouseCursorLocation()))
		{
			EnemyTownhallWidget = CreateWidget<UUserWidget>(GetWorld(), EnemyTownhallWidgetClass);
			if (EnemyTownhallWidget)
			{
				EnemyTownhallWidget->AddToViewport();
			}
		}
		else
		{
			LastSelectedOwnBarrackActor = GetClickedBarrack(RTSGameMode->PlayerOneInfo);
			LastSelectedEnemyBarrackActor = GetClickedBarrack(RTSGameMode->PlayerTwoInfo);

			if (LastSelectedOwnBarrackActor)
			{
				OwnBarrackWidget = CreateWidget<UUserWidget>(GetWorld(), OwnBarrackWidgetClass);
				if (OwnBarrackWidget)
				{
					OwnBarrackWidget->AddToViewport();
				}
			}
			else if (LastSelectedEnemyBarrackActor)
			{
				EnemyBarrackWidget = CreateWidget<UUserWidget>(GetWorld(), EnemyBarrackWidgetClass);
				if (EnemyBarrackWidget)
				{
					EnemyBarrackWidget->AddToViewport();
				}
			}
		}
	}
}

void ARTSController::SpawnMine(UPlayerInfo* PlayerInfo)
{
	if (AMineActor::BoardPrice < PlayerInfo->GetBoardCount() && AMineActor::StonePrice < PlayerInfo->GetStoneCount())
	{
		PlayerInfo->DecreaseBoardCount(AMineActor::BoardPrice);
		PlayerInfo->DecreaseStoneCount(AMineActor::StonePrice);
		FVector Scale(0.58f, 0.58f, 0.58f);
		SpawnPlayerBuilding(TEXT("MineActor"), Scale, PlayerInfo);
	}
}

void ARTSController::SpawnLumberjackHut(UPlayerInfo* PlayerInfo)
{
	if (ALumberjackHutActor::BoardPrice < PlayerInfo->GetBoardCount() && ALumberjackHutActor::StonePrice < PlayerInfo->GetStoneCount())
	{
		PlayerInfo->DecreaseBoardCount(ALumberjackHutActor::BoardPrice);
		PlayerInfo->DecreaseStoneCount(ALumberjackHutActor::StonePrice);
		FVector Scale(0.5f, 0.5f, 0.5f);
		SpawnPlayerBuilding(TEXT("LumberjackHutActor"), Scale, PlayerInfo);
	}
}

void ARTSController::SpawnForge(UPlayerInfo* PlayerInfo)
{
	if (AForgeActor::BoardPrice < PlayerInfo->GetBoardCount() && AForgeActor::StonePrice < PlayerInfo->GetStoneCount())
	{
		PlayerInfo->DecreaseBoardCount(AForgeActor::BoardPrice);
		PlayerInfo->DecreaseStoneCount(AForgeActor::StonePrice);
		FVector Scale(1.0f, 1.0f, 1.0f);
		SpawnPlayerBuilding(TEXT("ForgeActor"), Scale, PlayerInfo);
	}
}

void ARTSController::SpawnSawmill(UPlayerInfo* PlayerInfo)
{
	if (ASawmillActor::BoardPrice < PlayerInfo->GetBoardCount() && ASawmillActor::StonePrice < PlayerInfo->GetStoneCount())
	{
		PlayerInfo->DecreaseBoardCount(ASawmillActor::BoardPrice);
		PlayerInfo->DecreaseStoneCount(ASawmillActor::StonePrice);
		FVector Scale(1.2f, 1.2f, 1.2f);
		SpawnPlayerBuilding(TEXT("SawmillActor"), Scale, PlayerInfo);
	}
}

void ARTSController::SpawnBarrack(UPlayerInfo* PlayerInfo)
{
	if (ABarrackActor::BoardPrice < PlayerInfo->GetBoardCount() && ABarrackActor::StonePrice < PlayerInfo->GetStoneCount())
	{
		PlayerInfo->DecreaseBoardCount(ABarrackActor::BoardPrice);
		PlayerInfo->DecreaseStoneCount(ABarrackActor::StonePrice);
		FVector Scale(0.57f, 0.57f, 0.57f);
		SpawnPlayerBuilding(TEXT("BarrackActor"), Scale, PlayerInfo);
	}
}

void ARTSController::SpawnBuilding(const FString& BuildingName, const FVector& Scale)
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	ControlledBuilding = Cast<ABuilding>(SpawnActorByName(GetWorld(), BuildingName, GetLandscapeMouseCursorLocation(), Rotation));
	ControlledBuilding->SetActorScale3D(Scale);
	ConrolledBuildingAABB = GetActorCornerLocations(ControlledBuilding);
	BuildingMode = true;
}

void ARTSController::SpawnPlayerBuilding(const FString& BuildingName, const FVector& Scale, UPlayerInfo* PlayerInfo)
{
	SpawnBuilding(BuildingName, Scale);
	ControlledBuilding->SetPlayerInfo(PlayerInfo);
}

AActor* ARTSController::SpawnActorByName(UWorld* World, const FString& ActorClassName, const FVector& Location, const FRotator& Rotation)
{
	UClass* ActorClass = FindObject<UClass>(ANY_PACKAGE, *ActorClassName);

	if (ActorClass)
	{
		return World->SpawnActor<AActor>(ActorClass, Location, Rotation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failded to find actor: " + ActorClassName));
		return nullptr;
	}
}

int ARTSController::GetAttackCount(ABarrackActor* BarrackActor, UPlayerInfo* EnemyInfo)
{
	int result = 0;
	for (AActor* Actor : EnemyInfo->PlayerMilitaryBuildings)
	{
		ABarrackActor* OtherBarrack = Cast<ABarrackActor>(Actor);
		if (OtherBarrack)
		{
			if (OtherBarrack->GetComponentsBoundingBox(true).ExpandBy(FVector(7000.0, 7000.0, 7000.0)).Intersect(BarrackActor->GetComponentsBoundingBox(true)))
			{
				result += OtherBarrack->GetMilitaryPower();
			}
		}
	}
	return result;
}

int ARTSController::GetTownhallAttackCount(AStaticMeshActor* StaticMeshActor, UPlayerInfo* EnemyInfo)
{
	int result = 0;
	for (AActor* Actor : EnemyInfo->PlayerMilitaryBuildings)
	{
		ABarrackActor* OtherBarrack = Cast<ABarrackActor>(Actor);
		if (OtherBarrack)
		{
			if (OtherBarrack->GetComponentsBoundingBox(true).ExpandBy(FVector(7000.0, 7000.0, 7000.0)).Intersect(StaticMeshActor->GetComponentsBoundingBox(true)))
			{
				result += OtherBarrack->GetMilitaryPower();
			}
		}
	}
	return result;
}

void ARTSController::AttackTownhall(AStaticMeshActor* StaticMeshActor, UPlayerInfo* EnemyInfo)
{
	if (EnemyInfo->GetTownhallMilitaryPower() < GetTownhallAttackCount(StaticMeshActor, EnemyInfo))
	{
		VictoryWidget = CreateWidget<UUserWidget>(GetWorld(), VictoryWidgetClass);
		if (VictoryWidget)
		{
			VictoryWidget->AddToViewport();
		}
	}
}
