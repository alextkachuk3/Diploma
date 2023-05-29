#include "RTSController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Engine/ObjectLibrary.h>
#include "Landscape.h"
#include "LandscapeComponent.h"

ARTSController::ARTSController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARTSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this, &ARTSController::OnInputStarted);
	}
}

void SpawnActorByName(UWorld* World, const FString& ActorClassName, const FVector& Location, const FRotator& Rotation)
{
	UClass* ActorClass = FindObject<UClass>(ANY_PACKAGE, *ActorClassName);

	if (ActorClass)
	{
		AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, Location, Rotation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failded to find actor: " + ActorClassName));
	}
}

void ARTSController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	FString ActorClassName = TEXT("Building");
	FVector Location(-19787.0, 15018.7, 154.7);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	SpawnActorByName(World, ActorClassName, Location, Rotation);
}

void ARTSController::OnInputStarted()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Click");

	FVector2D CursorPosition;
	GetMousePosition(CursorPosition.X, CursorPosition.Y);
	FVector WorldLocation, WorldDirection;

	if (UGameplayStatics::DeprojectScreenToWorld(this, CursorPosition, WorldLocation, WorldDirection))
	{
		UWorld* World = GetWorld();
		FString ActorClassName = TEXT("Building");
		// WorldLocation.Z = 154;
		// WorldDirection.Z = 154;
		//FVector Location(WorldLocation);
		FRotator Rotation(0.0f, 0.0f, 0.0f);

		FHitResult HitResult;

		ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldStatic;

		GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * 50000, TraceChannel);

		/*TArray<AActor*> LandscapeActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), LandscapeActors);

		ALandscape* Landscape = Cast<ALandscape>(LandscapeActors[0]);

		FVector LocalLocation = Landscape->GetTransform().InverseTransformPosition(FVector(HitResult.Location.X, HitResult.Location.Y, 0.0f));*/


		SpawnActorByName(World, ActorClassName, HitResult.Location, Rotation);

		//SpawnActorByName(World, ActorClassName, LocalLocation, Rotation);

	}
}
