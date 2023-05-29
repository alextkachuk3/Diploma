#include "ForgeActor.h"

AForgeActor::AForgeActor()
{
	FString MeshName = TEXT("ForgeModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(40.0);
}

void AForgeActor::Tick(float DeltaTime)
{

}
