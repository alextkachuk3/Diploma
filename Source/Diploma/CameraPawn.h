#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "CameraPawn.generated.h"

UCLASS()
class DIPLOMA_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		APlayerController* PlayerController;

	UPROPERTY()
		USceneComponent* RootScene;

	UPROPERTY()
		USpringArmComponent* SpringArm;

	UPROPERTY()
		UCameraComponent* CameraComponent;

	UFUNCTION()
		FVector GetCameraMoveDirection();

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 40;

	int ScreenSizeX;
	int ScreenSizeY;

	FVector CurrentCameraLocation;
	FVector CurrentCameraMoveDirection;

	float ScreenSizeToMarginProportion = 0.025;
	int Margin;

	float LeftMapBorder = -16000.0;
	float RightMapBorder = 21500.0;
	float UpperMapBorder = 12500.0;
	float BottomMapBorder = -30000.0;

	float MousePositionX;
	float MousePositionY;
	float CameraDirectionX;
	float CameraDirectionY;
};
