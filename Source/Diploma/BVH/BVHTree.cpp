#include "BVHTree.h"

BVHTree::BVHTree(const std::vector<FVector2D>& Objects) : Root(nullptr) {
	Root = BuildBVHTree(Objects);
}

BVHTree::~BVHTree()
{
	delete Root;
}

BVHNode* BVHTree::BuildBVHTree(const std::vector<FVector2D>& Objects)
{
	if (Objects.empty())
		return nullptr;

	BVHNode* Node = new BVHNode(Objects);

	if (Objects.size() == 1) {
		Node->Left = nullptr;
		Node->Right = nullptr;
	}
	else {
		int mid = (int)Objects.size() / 2;
		std::vector<FVector2D> leftObjects(Objects.begin(), Objects.begin() + mid);
		std::vector<FVector2D> rightObjects(Objects.begin() + mid, Objects.end());

		Node->Left = BuildBVHTree(leftObjects);
		Node->Right = BuildBVHTree(rightObjects);
	}

	return Node;
}

bool BVHTree::Intersects(const BoundingVolumeAABB& Volume) const
{
	return Intersects(Volume, Root);
}

bool BVHTree::Intersects(const BoundingVolumeAABB& Volume, const BVHNode* Node) const
{
	if (Node == nullptr)
		return false;

	if (Volume.Intersects(Node->Volume)) {
		for (const auto& obj : Node->Objects) {
			if (Volume.Intersects(BoundingVolumeAABB{ obj.X, obj.Y, obj.X, obj.Y }))
			{
				return true;
			}
		}

		if (Intersects(Volume, Node->Left))
			return true;
		if (Intersects(Volume, Node->Right))
			return true;
	}

	return false;
}