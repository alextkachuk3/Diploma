#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class DIPLOMA_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	ABuilding();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	static UStaticMesh* LoadStaticMeshByName(const FString& MeshName);

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

};
