#include "ForgeActor.h"

AForgeActor::AForgeActor()
{
	FString MeshName = TEXT("ForgeModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(30.0);
}

AForgeActor::AForgeActor(UPlayerInfo* OwnerStats)
{
	AForgeActor();
	this->OwnerInfo = OwnerStats;
}

void AForgeActor::Tick(float DeltaTime)
{
	if (OwnerInfo != nullptr)
	{
		if (OwnerInfo->GetIronCount() > 0)
		{
			OwnerInfo->DecreaseIronCount(1);
			OwnerInfo->IncreaseWeaponCount(1);
			UE_LOG(LogTemp, Display, TEXT("IRON COUNT:%d"), OwnerInfo->GetIronCount());
			UE_LOG(LogTemp, Display, TEXT("WEAPON COUNT:%d"), OwnerInfo->GetWeaponCount());
		}
	}
}
