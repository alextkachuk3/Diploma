#include "BoundingVolumeAABB.h"

BoundingVolumeAABB::BoundingVolumeAABB() : MinX(0), MinY(0), MaxX(0), MaxY(0) {}

BoundingVolumeAABB::BoundingVolumeAABB(const double& MinX, const double& MinY, const double& MaxX, const double& MaxY)
{
    this->MinX = MinX;
    this->MinY = MinY;
    this->MaxX = MaxX;
    this->MaxY = MaxY;
}

void BoundingVolumeAABB::Update(const std::vector<FVector2D>& Objects)
{
    if (Objects.empty())
        return;

    MinX = Objects[0].X;
    MinY = Objects[0].Y;
    MaxX = Objects[0].X;
    MaxY = Objects[0].Y;

    for (const auto& obj : Objects) {
        if (obj.X < MinX)
            MinX = obj.X;
        if (obj.Y < MinY)
            MinY = obj.Y;
        if (obj.X > MaxX)
            MaxX = obj.X;
        if (obj.Y > MaxY)
            MaxY = obj.Y;
    }
}

bool BoundingVolumeAABB::Intersects(const BoundingVolumeAABB& Other) const
{
    return !(MaxX < Other.MinX || MinX > Other.MaxX || MaxY < Other.MinY || MinY > Other.MaxY);
}
