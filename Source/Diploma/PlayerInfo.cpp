#include "PlayerInfo.h"

UPlayerInfo::UPlayerInfo()
{
	Reset();
}

void UPlayerInfo::IncreaseLumberCount(const int& Count)
{
	LumberCount += Count;
}

void UPlayerInfo::DecreaseLumberCount(const int& Count)
{
	LumberCount -= Count;
	if (LumberCount < 0)
		LumberCount = 0;
}

int UPlayerInfo::GetLumberCount()
{
	return LumberCount;
}

void UPlayerInfo::IncreaseBoardCount(const int& Count)
{
	BoardCount += Count;
}

void UPlayerInfo::DecreaseBoardCount(const int& Count)
{
	BoardCount -= Count;
	if (BoardCount < 0)
		BoardCount = 0;
}

int UPlayerInfo::GetBoardCount()
{
	return BoardCount;
}

void UPlayerInfo::IncreaseStoneCount(const int& Count)
{
	StoneCount += Count;
}

void UPlayerInfo::DecreaseStoneCount(const int& Count)
{
	StoneCount -= Count;
	if (StoneCount < 0)
		StoneCount = 0;
}

int UPlayerInfo::GetStoneCount()
{
	return StoneCount;
}

void UPlayerInfo::IncreaseIronCount(const int& Count)
{
	IronCount += Count;
}

void UPlayerInfo::DecreaseIronCount(const int& Count)
{
	IronCount -= Count;
	if (IronCount < 0)
		IronCount = 0;
}

int UPlayerInfo::GetIronCount()
{
	return IronCount;
}

void UPlayerInfo::IncreaseWeaponCount(const int& Count)
{
	WeaponCount += Count;
}

void UPlayerInfo::DecreaseWeaponCount(const int& Count)
{
	WeaponCount -= Count;
	if (WeaponCount < 0)
		WeaponCount = 0;
}

int UPlayerInfo::GetWeaponCount()
{
	return WeaponCount;
}

void UPlayerInfo::Reset()
{
	LumberCount = 0;
	BoardCount = 0;
	StoneCount = 0;
	IronCount = 0;
	WeaponCount = 0;

	PlayerBuildings.clear();
	PlayerMilitaryBuildings.clear();
}

void UPlayerInfo::AddBuilding(AActor* Building)
{
	PlayerBuildings.push_back(Building);
}

void UPlayerInfo::RemoveBuilding(AActor* Building)
{
	PlayerBuildings.erase(std::remove(PlayerBuildings.begin(), PlayerBuildings.end(), Building), PlayerBuildings.end());
}

void UPlayerInfo::AddMilitaryBuilding(AActor* Building)
{
	PlayerMilitaryBuildings.push_back(Building);
}

void UPlayerInfo::RemoveMilitaryBuilding(AActor* Building)
{
	PlayerMilitaryBuildings.erase(std::remove(PlayerBuildings.begin(), PlayerBuildings.end(), Building), PlayerBuildings.end());
}

bool UPlayerInfo::IntersectOtherBuilding(AActor* Building)
{
	for (AActor* OtherBuilding : PlayerBuildings)
	{
		if (OtherBuilding->GetComponentsBoundingBox(true).Intersect(Building->GetComponentsBoundingBox(true)))
		{
			return true;
		}			
	}
	for (AActor* OtherBuilding : PlayerMilitaryBuildings)
	{
		if (OtherBuilding->GetComponentsBoundingBox(true).Intersect(Building->GetComponentsBoundingBox(true)))
		{
			return true;
		}
	}

	return false;
}

bool UPlayerInfo::InsideMilitaryBorder(AActor* Building)
{
	for (AActor* OtherBuilding : PlayerMilitaryBuildings)
	{
		if (OtherBuilding->GetComponentsBoundingBox(true).ExpandBy(BorderExpand).Intersect(Building->GetComponentsBoundingBox(true)))
		{
			return true;
		}
	}
	return false;
}
