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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Lumberjack hut tick!"));
	if (OwnerInfo != nullptr)
	{
		OwnerInfo->IncreaseLumberCount(1);
		UE_LOG(LogTemp, Display, TEXT("LUMBER COUNT:%d"), OwnerInfo->GetLumberCount());
	}
}
