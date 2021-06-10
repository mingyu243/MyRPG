#include "Weapon.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WeaponMesh(TEXT("StaticMesh'/Game/ModularRPGHeroesPolyart/Meshes/Weapons/Sword01SM.Sword01SM'"));
	if (SM_WeaponMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SM_WeaponMesh.Object);
	}
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponType = EWeaponType::SWORD_SHIELD;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

UStaticMesh* AWeapon::GetWeaponMesh()
{
	// ���� ������Ʈ���� Mesh�� �������. ������Ʈ �ѱ�� �ȵ�¡.
	//return Mesh;
	return Mesh->GetStaticMesh();
}

EWeaponType AWeapon::GetWeaponType()
{
	return WeaponType;
}

