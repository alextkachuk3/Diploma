#include "Building.h"

#include "Engine/ObjectLibrary.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	FString MeshName = TEXT("ForgeModel");
	UStaticMesh* StaticMesh = LoadStaticMeshByName(MeshName);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	SetRootComponent(StaticMeshComponent);
}

void ABuilding::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Building");
	Super::BeginPlay();
}

UStaticMesh* ABuilding::LoadStaticMeshByName(const FString& MeshName)
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UStaticMesh::StaticClass(), false, true);
	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Models"));
	ObjectLibrary->LoadAssetsFromAssetData();

	TArray<FAssetData> AssetDataList;
	ObjectLibrary->GetAssetDataList(AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (AssetData.AssetName.ToString() == MeshName)
		{
			UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset());
			if (StaticMesh)
			{
				return StaticMesh;
			}
		}
	}

	return nullptr;
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

