#pragma once

#include "CoreMinimal.h"
#include "BoundingVolumeAABB.h"

class DIPLOMA_API BVHNode
{
public:
    BoundingVolumeAABB Volume;
    std::vector<FVector2D> Objects;
    BVHNode* Left;
    BVHNode* Right;

    BVHNode(const std::vector<FVector2D>& objs);

    ~BVHNode();
};
