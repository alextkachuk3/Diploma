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

	UPROPERTY()
		int ScreenSizeX;
	UPROPERTY()
		int ScreenSizeY;


	UPROPERTY()
		float ScreenSizeToMarginProportion = 0.025;
	UPROPERTY()
		int Margin;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 40;

	UPROPERTY()
		float MousePositionX;
	UPROPERTY()
		float MousePositionY;
	UPROPERTY()
		float CameraDirectionX;
	UPROPERTY()
		float CameraDirectionY;
};
