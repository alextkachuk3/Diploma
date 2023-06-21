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
	if (OwnerInfo != nullptr)
	{
		OwnerInfo->IncreaseIronCount(1);
		OwnerInfo->IncreaseStoneCount(2);
		UE_LOG(LogTemp, Display, TEXT("IRON COUNT:%d"), OwnerInfo->GetIronCount());
		UE_LOG(LogTemp, Display, TEXT("STONE COUNT:%d"), OwnerInfo->GetStoneCount());
	}
}
