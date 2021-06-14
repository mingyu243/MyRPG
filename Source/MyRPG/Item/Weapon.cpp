#include "Weapon.h"

#include "../CustomDataTables.h"

AWeapon::AWeapon()
{
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

FWeaponData* AWeapon::GetWeaponData()
{
	return CurrentWeaponData;
}
