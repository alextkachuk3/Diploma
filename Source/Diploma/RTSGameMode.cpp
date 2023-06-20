#include "RTSGameMode.h"


void ARTSGameMode::BeginPlay()
{
	TreesLocations = GetAllTreesLocations();
	MapTreesBVHTree = new BVHTree(TreesLocations);
}

std::vector<FVector2D> ARTSGameMode::GetAllTreesLocations()
{
	std::vector<FVector2D> result;
	AInstancedFoliageActor* InstancedFoliageActor = nullptr;
	UWorld* World = GetWorld();
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), ActorArray);

	for (AActor* Actor : ActorArray)
	{
		FString ActorName = Actor->GetName();
		if (ActorName == TEXT("InstancedFoliageActor_0"))
		{
			InstancedFoliageActor = Cast<AInstancedFoliageActor>(Actor);

			if (InstancedFoliageActor)
			{
				auto FoliageComponents = InstancedFoliageActor->GetComponentsByClass(UFoliageInstancedStaticMeshComponent::StaticClass());
				for (auto& Comp : FoliageComponents)
				{
					auto FoliageComponent = Cast<UFoliageInstancedStaticMeshComponent>(Comp);
					if (FoliageComponent != nullptr)
					{
						UStaticMesh* Mesh = FoliageComponent->GetStaticMesh();
						auto InstanceCount = FoliageComponent->GetInstanceCount();

						UE_LOG(LogTemp, Display, TEXT("FoliageComp Mesh:%s Instances:%d"), *Mesh->GetName(), FoliageComponent->GetInstanceCount());

						for (int i = 0; i < InstanceCount; ++i)
						{
							FTransform InstanceTransform;
							FoliageComponent->GetInstanceTransform(i, OUT InstanceTransform, true);
							result.push_back(FVector2D(InstanceTransform.GetTranslation().X, InstanceTransform.GetTranslation().Y));
						}
					}
				}
			}
		}
	}

	return result;
}

ARTSGameMode::ARTSGameMode()
{
	PlayerOneInfo = NewObject<UPlayerInfo>();
	PlayerTwoInfo = NewObject<UPlayerInfo>();
}
