#pragma once

#include "CoreMinimal.h"
#include "BVHNode.h"

class DIPLOMA_API BVHTree
{
public:        
    BVHTree(const std::vector<FVector2D>& Objects);

    ~BVHTree();

    BVHNode* BuildBVHTree(const std::vector<FVector2D>& Objects);

    bool Intersects(const BoundingVolumeAABB& Volume) const;

private:
    BVHNode* Root;

    bool Intersects(const BoundingVolumeAABB& Volume, const BVHNode* Node) const;
};
