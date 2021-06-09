#include "EquipmentComponent.h"

#include "../Item/Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

UEquipmentComponent::UEquipmentComponent()
{
	Face = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FACE"));
	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HAIR"));
	Glove = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GLOVE"));
	Shoe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SHOE"));
	HeadGears = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HEADGEARS"));
	ShoulderPad = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SHOULDERPAD"));
	Belt = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BELT"));

	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHIELD"));
	Shield->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTWEAPON"));
	RightWeapon->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	Backpack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BACKPACK"));
	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTWEAPON"));
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::Init(USkeletalMeshComponent* NewBodyMesh)
{
	BodyMesh = NewBodyMesh;

	Face->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	FName WeaponSocket(TEXT("hand_rSocket"));
	RightWeapon->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocket);
}

AWeapon* UEquipmentComponent::GetWeapon()
{
	return CurrentWeapon;
}

void UEquipmentComponent::SetWeapon(AWeapon* NewWeapon)
{
	CurrentWeapon = NewWeapon;
	//RightWeapon->SetStaticMesh(NewWeapon->GetWeaponMesh());
}
