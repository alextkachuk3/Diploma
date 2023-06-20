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
