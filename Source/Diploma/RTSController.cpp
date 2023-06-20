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
	if (BuildingMode)
	{
		FVector2D CursorPosition;
		GetMousePosition(CursorPosition.X, CursorPosition.Y);
		FVector WorldLocation, WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(this, CursorPosition, WorldLocation, WorldDirection);
		UWorld* World = GetWorld();
		FHitResult HitResult;
		ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldStatic;
		GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 50000, TraceChannel);
		ControlledBuilding->SetActorLocation(HitResult.Location);
		ConrolledBuildingAABB = GetActorCornerLocations(ControlledBuilding);
	}
}

void ARTSController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
}

BoundingVolumeAABB ARTSController::GetActorCornerLocations(AActor* Actor)
{
	FBox BB = Actor->GetComponentsBoundingBox(true);
	return BoundingVolumeAABB(BB.Min.X, BB.Min.Y, BB.Max.X, BB.Max.Y);
}

bool ARTSController::BuildingInsideBorder(AActor* Actor)
{
	FBox BB = Actor->GetComponentsBoundingBox(true);
	return BB.Min.X > MinXBorder && BB.Min.Y > MinYBorder && BB.Max.X < MaxXBorder && BB.Max.Y < MaxYBorder;
}

void ARTSController::LeftMouseButtonClickAction()
{
	if (!RTSGameMode->MapTreesBVHTree->Intersects(ConrolledBuildingAABB) && BuildingInsideBorder(ControlledBuilding))
	{
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
}

void ARTSController::SpawnMine()
{
	FVector Scale(0.58f, 0.58f, 0.58f);
	SpawnPlayerBuilding(TEXT("MineActor"), Scale, RTSGameMode->PlayerOneInfo);
}

void ARTSController::SpawnLumberjackHut()
{
	FVector Scale(0.5f, 0.5f, 0.5f);
	SpawnPlayerBuilding(TEXT("LumberjackHutActor"), Scale, RTSGameMode->PlayerOneInfo);
}

void ARTSController::SpawnForge()
{
	FVector Scale(1.0f, 1.0f, 1.0f);
	SpawnPlayerBuilding(TEXT("ForgeActor"), Scale, RTSGameMode->PlayerOneInfo);
}

void ARTSController::SpawnSawmill()
{
	FVector Scale(1.2f, 1.2f, 1.2f);
	SpawnPlayerBuilding(TEXT("SawmillActor"), Scale, RTSGameMode->PlayerOneInfo);
}

void ARTSController::SpawnBarrack()
{
	FVector Scale(0.57f, 0.57f, 0.57f);
	SpawnBuilding(TEXT("BarrackActor"), Scale);
}

void ARTSController::SpawnBuilding(const FString& BuildingName, const FVector& Scale)
{
	FVector2D CursorPosition;
	GetMousePosition(CursorPosition.X, CursorPosition.Y);
	FVector WorldLocation, WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, CursorPosition, WorldLocation, WorldDirection);
	UWorld* World = GetWorld();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FHitResult HitResult;
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldStatic;
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 50000, TraceChannel);
	ControlledBuilding = Cast<ABuilding>(SpawnActorByName(World, BuildingName, HitResult.Location, Rotation));
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
