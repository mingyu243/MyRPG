#include "Weapon.h"

AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPONMESH"));
	RootComponent = WeaponMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WeaponMesh(TEXT("StaticMesh'/Game/ModularRPGHeroesPolyart/Meshes/Weapons/Sword01SM.Sword01SM'"));
	if (SM_WeaponMesh.Succeeded())
	{
		WeaponMesh->SetStaticMesh(SM_WeaponMesh.Object);
	}
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

