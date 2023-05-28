#include "RTSController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Engine/ObjectLibrary.h>

UInputAction* LoadInputActionByName(const FString& InputName)
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UInputAction::StaticClass(), false, true);
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Input/Actions"));
	ObjectLibrary->LoadAssetsFromAssetData();

	TArray<FAssetData> AssetDataList;
	ObjectLibrary->GetAssetDataList(AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (AssetData.AssetName.ToString() == InputName)
		{
			UInputAction* InputAction = Cast<UInputAction>(AssetData.GetAsset());
			if (InputAction)
			{
				return InputAction;
			}
		}
	}

	return nullptr;
}

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
    // Find the actor class by name
    UClass* ActorClass = FindObject<UClass>(ANY_PACKAGE, *ActorClassName);

    if (ActorClass)
    {
        // Spawn the actor
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
}
