#include "EquipmentComponent.h"

#include "../Item/Weapon.h"
#include "../MyGameInstance.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

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
	Backpack->SetRelativeLocationAndRotation(FVector(0.0f, -4.0f, -6.4f), FRotator(0.0f, -2.8f, 0.0f));
	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTWEAPON"));
	LeftWeapon->SetRelativeLocationAndRotation(FVector(11.0f, -1.8f, -1.5f), FRotator(0.0f, 90.0f, 0.0f));
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::Init(USkeletalMeshComponent* NewBodyMesh)
{
	BodyMesh = NewBodyMesh;
	
	Face->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Hair->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Glove->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Shoe->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	HeadGears->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ShoulderPad->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Belt->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	Shield->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	RightWeapon->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));
	Backpack->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Backpack"));
	LeftWeapon->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));

	//FName Socket_Backpack(TEXT("Backpack"));
	//Backpack->SetupAttachment(BodyMesh, Socket_Backpack);

	Face->SetMasterPoseComponent(BodyMesh);
	Hair->SetMasterPoseComponent(BodyMesh);
	Glove->SetMasterPoseComponent(BodyMesh);
}

void UEquipmentComponent::SetEquipment(UEquipment* Equipment)
{
	EEquipmentType Type = Equipment->GetEquipmentData()->Enum_EquipmentType;
	
	USkeletalMesh* LoadedMesh_Skeletal = LoadObject<USkeletalMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh));
	switch (Type)
	{
	case EEquipmentType::WEAPON:
		break;
	case EEquipmentType::BACKPACK:
	{
		UE_LOG(LogClass, Warning, TEXT("asd"));
		UStaticMesh* LoadedMesh_Static = LoadObject<UStaticMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh));
		Backpack->SetStaticMesh(LoadedMesh_Static);
		break;
	}
	case EEquipmentType::FACE:
		Face->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::HAIR:
		Hair->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::GLOVE:
		Glove->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::BODY:
		BodyMesh->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::SHOE:
		Shoe->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::HEADGEARS:
		HeadGears->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::SHOULDERPAD:
		ShoulderPad->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	case EEquipmentType::BELT:
		Belt->SetSkeletalMesh(LoadedMesh_Skeletal);
		break;
	default:
		break;
	}
}

//AWeapon* UEquipmentComponent::GetWeapon()
//{
//	return nullptr;//CurrentWeapon;
//}
//
//void UEquipmentComponent::SetWeapon(AWeapon* NewWeapon)
//{
//	//CurrentWeapon = NewWeapon;
//	//RightWeapon->SetStaticMesh(NewWeapon->GetWeaponMesh());
//}
