#include "Weapon.h"

AWeapon::AWeapon()
{

	WeaponType = EWeaponType::SWORD_SHIELD;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

EWeaponType AWeapon::GetWeaponType()
{
	return WeaponType;
}

