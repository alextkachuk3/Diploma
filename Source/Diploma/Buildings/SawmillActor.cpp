#include "SawmillActor.h"

ASawmillActor::ASawmillActor()
{
	FString MeshName = TEXT("SawmillModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(20.0);
}

void ASawmillActor::Tick(float DeltaTime)
{

}
