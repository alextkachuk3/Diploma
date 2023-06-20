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

	/*AInstancedFoliageActor* InstancedFoliageActor = nullptr;

	UWorld* World = GetWorld();

	UClass* ActorClass = AActor::StaticClass();
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(World, ActorClass, ActorArray);

	for (AActor* Actor : ActorArray)
	{
		FString ActorName = Actor->GetName();
		if (ActorName == TEXT("InstancedFoliageActor_0"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());
			InstancedFoliageActor = Cast<AInstancedFoliageActor>(Actor);
			UE_LOG(LogTemp, Warning, TEXT("LOL"));

			if (InstancedFoliageActor)
			{
				auto FoliageComponents = InstancedFoliageActor->GetComponentsByClass(UFoliageInstancedStaticMeshComponent::StaticClass());
				for (auto& Comp : FoliageComponents)
				{
					auto FoliageComponent = Cast<UFoliageInstancedStaticMeshComponent>(Comp);
					if (FoliageComponent != nullptr)
					{
						UStaticMesh* Mesh = FoliageComponent->GetStaticMesh();
						auto InstanceCount = FoliageComponent->GetInstanceCount();

						UE_LOG(LogTemp, Display, TEXT("FoliageComp Mesh:%s Instances:%d"), *Mesh->GetName(), FoliageComponent->GetInstanceCount());

						for (int i = 0; i < InstanceCount; ++i)
						{
							FTransform InstanceTransform;
							FoliageComponent->GetInstanceTransform(i, OUT InstanceTransform, true);

							UE_LOG(LogTemp, Display, TEXT("%s[%d] %s"), *Mesh->GetName(), i, *InstanceTransform.ToString());
						}
					}
				}
			}
		}
	}*/
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
	UE_LOG(LogTemp, Display, TEXT("TEST C:%d"), RTSGameMode->PlayerOneStats.GetBoardCount());
	if (!RTSGameMode->MapTreesBVHTree->Intersects(ConrolledBuildingAABB))
	{
		BuildingMode = false;
	}
}

void ARTSController::SpawnMine()
{
	FVector Scale(0.58f, 0.58f, 0.58f);
	SpawnBuilding(TEXT("MineActor"), Scale);
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
	ControlledBuilding = SpawnActorByName(World, BuildingName, HitResult.Location, Rotation);
	ControlledBuilding->SetActorScale3D(Scale);
	ConrolledBuildingAABB = GetActorCornerLocations(ControlledBuilding);
	BuildingMode = true;
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
