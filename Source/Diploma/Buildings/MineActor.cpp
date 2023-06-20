#include "MineActor.h"

AMineActor::AMineActor()
{
	FString MeshName = TEXT("MineModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(30.0);
	OwnerInfo = nullptr;
}

AMineActor::AMineActor(UPlayerInfo* OwnerStats)
{
	AMineActor();
	this->OwnerInfo = OwnerStats;
}

void AMineActor::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Mine tick!"));
	if (OwnerInfo != nullptr)
	{
		OwnerInfo->IncreaseIronCount(1);
		OwnerInfo->IncreaseStoneCount(2);
		UE_LOG(LogTemp, Display, TEXT("IRON COUNT:%d"), OwnerInfo->GetIronCount());
		UE_LOG(LogTemp, Display, TEXT("STONE COUNT:%d"), OwnerInfo->GetStoneCount());
	}
}
