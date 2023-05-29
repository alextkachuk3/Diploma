#include "MineActor.h"

AMineActor::AMineActor()
{
	FString MeshName = TEXT("MineModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(30.0);
}

void AMineActor::Tick(float DeltaTime)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Mine tick!"));
}
