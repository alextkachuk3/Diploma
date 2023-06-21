#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlayerInfo.h"
#include "Building.generated.h"

UCLASS()
class DIPLOMA_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	ABuilding();
	ABuilding(UPlayerInfo* OwnerStats);
	virtual void Tick(float DeltaTime) override;
	void SetPlayerInfo(UPlayerInfo* PlayerInfo);
		

protected:
	virtual void BeginPlay() override;
	static UStaticMesh* LoadStaticMeshByName(const FString& MeshName);
	void SetStaticMesh(const FString& MeshName);
	UPlayerInfo* OwnerInfo;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;
};
