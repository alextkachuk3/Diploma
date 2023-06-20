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

	//UE_LOG(LogTemp, Display, TEXT("TEST C:%d"), meow->PlayerOneStats.GetBoardCount());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ARTSController::OnInputStarted);
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

void ARTSController::OnInputStarted()
{
	if (!RTSGameMode->MapTreesBVHTree->Intersects(ConrolledBuildingAABB))
	{
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
	SpawnBuilding(TEXT("LumberjackHutActor"), Scale);
}

void ARTSController::SpawnForge()
{
	FVector Scale(1.0f, 1.0f, 1.0f);
	SpawnBuilding(TEXT("ForgeActor"), Scale);
}

void ARTSController::SpawnSawmill()
{
	FVector Scale(1.2f, 1.2f, 1.2f);
	SpawnBuilding(TEXT("SawmillActor"), Scale);
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
