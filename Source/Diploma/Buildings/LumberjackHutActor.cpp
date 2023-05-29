#include "LumberjackHutActor.h"

ALumberjackHutActor::ALumberjackHutActor()
{
	FString MeshName = TEXT("LumberjacksHutModel");
	SetStaticMesh(MeshName);
	SetActorTickInterval(20.0);
}

void ALumberjackHutActor::Tick(float DeltaTime)
{

}
