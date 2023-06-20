#include "Building.h"

#include "Engine/ObjectLibrary.h"

void ABuilding::BeginPlay()
{
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

void ABuilding::SetStaticMesh(const FString& MeshName)
{
	UStaticMesh* StaticMesh = LoadStaticMeshByName(MeshName);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	SetRootComponent(StaticMeshComponent);
}

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	FString MeshName = TEXT("ForgeModel");
	SetActorEnableCollision(false);
}

ABuilding::ABuilding(UPlayerInfo* OwnerStats)
{
	PrimaryActorTick.bCanEverTick = true;
	FString MeshName = TEXT("ForgeModel");
	SetActorEnableCollision(false);
	this->OwnerInfo = OwnerStats;
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::SetPlayerInfo(UPlayerInfo* PlayerInfo)
{
	this->OwnerInfo = PlayerInfo;
}

