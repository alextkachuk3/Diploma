#include "BarrackActor.h"

ABarrackActor::ABarrackActor()
{
	FString MeshName = TEXT("BarrackModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(40.0);
}

void ABarrackActor::Tick(float DeltaTime)
{

}
