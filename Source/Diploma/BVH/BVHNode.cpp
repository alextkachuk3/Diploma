#include "BVHNode.h"

BVHNode::BVHNode(const std::vector<FVector2D>& objs) : Objects(objs), Left(nullptr), Right(nullptr)
{
    Volume.Update(Objects);
}

BVHNode::~BVHNode()
{
    delete Left;
    delete Right;
}
