#include "Weapon.h"

#include "../CustomDataTables.h"

void AWeapon::Init(int32 index)
{
	Super::Init(index);
}

void AWeapon::Use()
{
	Super::Use();
}

FWeaponData* AWeapon::GetWeaponData()
{
	return CurrentWeaponData;
}
