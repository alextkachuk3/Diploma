#pragma once

#include "CoreMinimal.h"


class DIPLOMA_API BoundingVolumeAABB
{
public:
	
    double MinX;
    double MinY;
    double MaxX;
    double MaxY;

    BoundingVolumeAABB();

    BoundingVolumeAABB(const double& MinX, const double& MinY, const double& MaxX, const double& MaxY);

    BoundingVolumeAABB(FBox Box);

    void Update(const std::vector<FVector2D>& Objects);

    bool Intersects(const BoundingVolumeAABB& Other) const;
};
