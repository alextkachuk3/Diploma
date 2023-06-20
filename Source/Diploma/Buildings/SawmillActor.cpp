#include "SawmillActor.h"

ASawmillActor::ASawmillActor()
{
	FString MeshName = TEXT("SawmillModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(30.0);
}

ASawmillActor::ASawmillActor(UPlayerInfo* OwnerStats)
{
	ASawmillActor();
	this->OwnerInfo = OwnerStats;
}

void ASawmillActor::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sawmill hut tick!"));
	if (OwnerInfo != nullptr)
	{
		if (OwnerInfo->GetLumberCount() > 0)
		{
			OwnerInfo->DecreaseLumberCount(1);
			OwnerInfo->IncreaseBoardCount(1);
			UE_LOG(LogTemp, Display, TEXT("LUMBER COUNT:%d"), OwnerInfo->GetLumberCount());
			UE_LOG(LogTemp, Display, TEXT("BOARD COUNT:%d"), OwnerInfo->GetBoardCount());
		}		
	}
}
