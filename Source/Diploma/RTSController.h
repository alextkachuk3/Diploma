#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	UFUNCTION(BlueprintCallable)
		void OnInputStarted();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay();
};
