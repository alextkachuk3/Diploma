#include "CameraPawn.h"
#include "RTSController.h"
#include <Kismet/GameplayStatics.h>

ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);

	Margin = (ScreenSizeX + ScreenSizeY) * ScreenSizeToMarginProportion;
	UE_LOG(LogTemp, Warning, TEXT("Screen size x: %d"), ScreenSizeX);
	UE_LOG(LogTemp, Warning, TEXT("Screen size y: %d"), ScreenSizeY);
}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentCameraMoveDirection = GetCameraMoveDirection();
	CurrentCameraLocation = GetActorLocation();
	double NewXLocation = CurrentCameraLocation.X + CurrentCameraMoveDirection.X;
	double NewYLocation = CurrentCameraLocation.Y + CurrentCameraMoveDirection.Y;
	if(UpperMapBorder < NewXLocation || BottomMapBorder > NewXLocation)
	{
		CurrentCameraMoveDirection.X = 0;
	}
	if (LeftMapBorder > NewYLocation || RightMapBorder < NewYLocation)
	{
		CurrentCameraMoveDirection.Y = 0;
	}
	AddActorWorldOffset(CurrentCameraMoveDirection);
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FVector ACameraPawn::GetCameraMoveDirection()
{
	PlayerController->GetMousePosition(MousePositionX, MousePositionY);

	CameraDirectionX = 0;
	CameraDirectionY = 0;

	if (MousePositionX <= Margin)
	{
		CameraDirectionY = -MoveSpeed;
	}
	if (MousePositionY <= Margin)
	{
		CameraDirectionX = MoveSpeed;
	}
	if (MousePositionX >= ScreenSizeX - Margin)
	{
		CameraDirectionY = MoveSpeed;
	}
	if (MousePositionY >= ScreenSizeY - Margin)
	{
		CameraDirectionX = -MoveSpeed;
	}

	return FVector(CameraDirectionX, CameraDirectionY, 0);
}

