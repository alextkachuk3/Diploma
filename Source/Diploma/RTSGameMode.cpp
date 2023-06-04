#include "RTSGameMode.h"
#include "RTSController.h"

ARTSGameMode::ARTSGameMode()
{
	MapTreesBVHTree = new BVHTree(std::vector<FVector2D>());
}
