#include "BarrackActor.h"

ABarrackActor::ABarrackActor()
{
	FString MeshName = TEXT("BarrackModel");
	SetStaticMesh(MeshName);
}

ABarrackActor::ABarrackActor(UPlayerInfo* OwnerStats)
{
	ABarrackActor();
	this->OwnerInfo = OwnerStats;
}

void ABarrackActor::Tick(float DeltaTime)
{

}

void ABarrackActor::IncreaseMilitaryPower()
{
	if (OwnerInfo)
	{
		if (MilitaryPower < MaxMilitaryPower && OwnerInfo->GetWeaponCount() > 0)
		{
			OwnerInfo->DecreaseWeaponCount(1);
			MilitaryPower++;
		}
	}
}

void ABarrackActor::DecreaseMilitaryPower(const int& Count)
{
	MilitaryPower -= Count;
	if (MilitaryPower < 0)
	{
		MilitaryPower = 0;
	}
}

int ABarrackActor::GetMilitaryPower()
{
	return MilitaryPower;
}
