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

void UPlayerInfo::IncreaseTownhallMilitaryPower()
{
	if (TownhallMilitaryPower < MaxTownhallMilitaryPower && WeaponCount > 0)
	{
		WeaponCount--;
		TownhallMilitaryPower++;
	}
}

void UPlayerInfo::DecreaseTownhallMilitaryPower(const int& Count)
{
	TownhallMilitaryPower -= Count;
	if (TownhallMilitaryPower < 0)
	{
		TownhallMilitaryPower = 0;
	}
}

int UPlayerInfo::GetTownhallMilitaryPower()
{
	return TownhallMilitaryPower;
}

void UPlayerInfo::Reset()
{
	LumberCount = 30;
	BoardCount = 30;
	StoneCount = 30;
	IronCount = 30;
	WeaponCount = 0;
	TownhallMilitaryPower = 5;

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

AActor* UPlayerInfo::ClickedMilitaryBuilding(const FVector& Location)
{
	for (auto Building : PlayerMilitaryBuildings)
	{
		if (Building->GetComponentsBoundingBox(true).IsInside(Location))
		{
			return Building;
		}
	}
	return nullptr;
}
