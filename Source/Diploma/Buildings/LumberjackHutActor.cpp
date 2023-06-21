#include "LumberjackHutActor.h"

ALumberjackHutActor::ALumberjackHutActor()
{
	FString MeshName = TEXT("LumberjacksHutModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(30.0);
}

ALumberjackHutActor::ALumberjackHutActor(UPlayerInfo* OwnerStats)
{
	ALumberjackHutActor();
	this->OwnerInfo = OwnerStats;
}

void ALumberjackHutActor::Tick(float DeltaTime)
{
	if (OwnerInfo != nullptr)
	{
		OwnerInfo->IncreaseLumberCount(1);
		UE_LOG(LogTemp, Display, TEXT("LUMBER COUNT:%d"), OwnerInfo->GetLumberCount());
	}
}
