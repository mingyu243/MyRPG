#include "EquipmentComponent.h"

#include "../Item/Weapon.h"
#include "../MyGameInstance.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

UEquipmentComponent::UEquipmentComponent()
{
	// Create Skeltal Parts.
	int32 Length = (uint8)ESkeletalMeshPartsType::E_ELEMENT_COUNT;
	SkeletalEquipmentArray.Reserve(Length);
	SkeletalMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		SkeletalEquipmentArray.Add(NewObject<UEquipment>()); 
		
		FName name = *FString::Printf(TEXT("Sekeltal %i"), i);
		SkeletalMeshArray.Add(CreateDefaultSubobject<USkeletalMeshComponent>(name));
	}

	// Create Static Parts.
	Length = (uint8)EStaticMeshPartsType::E_ELEMENT_COUNT;
	StaticEquipmentArray.Reserve(Length);
	StaticMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		StaticEquipmentArray.Add(NewObject<UEquipment>());

		FName name = *FString::Printf(TEXT("Static %i"), i);
		StaticMeshArray.Add(CreateDefaultSubobject<UStaticMeshComponent>(name));
	}
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_SHIELD]->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_WEAPON_LEFT]->SetRelativeLocationAndRotation(FVector(11.0f, -1.8f, -1.5f), FRotator(0.0f, 90.0f, 0.0f));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_WEAPON_RIGHT]->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_BACKPACK]->SetRelativeLocationAndRotation(FVector(0.0f, -4.0f, -6.4f), FRotator(0.0f, -2.8f, 0.0f));
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::Init(USkeletalMeshComponent* NewBodyMesh)
{
	// 기준이 되는 BodyMesh를 설정.
	BodyMesh = NewBodyMesh;

	// BodyMesh에 MeshComponent들을 Attach한다.
	int32 Length = (uint8)ESkeletalMeshPartsType::E_ELEMENT_COUNT;
	for (int i = 0; i < Length; i++)
	{
		if ((ESkeletalMeshPartsType)i == ESkeletalMeshPartsType::E_BODYMESH)
		{
			continue; // BodyMesh는 중심이므로, AttachToComponent를 하면 안 됨.
		}
		SkeletalMeshArray[i]->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
		SkeletalMeshArray[i]->SetMasterPoseComponent(BodyMesh);
	}

	StaticMeshArray[(uint8)EStaticMeshPartsType::E_SHIELD]->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_WEAPON_RIGHT]->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_WEAPON_LEFT]->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	StaticMeshArray[(uint8)EStaticMeshPartsType::E_BACKPACK]->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Backpack"));
}

void UEquipmentComponent::SetEquipment(UEquipment* Equipment)
{
	EEquipmentType Type = Equipment->GetEquipmentData()->Enum_EquipmentType;
	
	USkeletalMesh* LoadedMesh_Skeletal = LoadObject<USkeletalMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh));
	switch (Type)
	{
	case EEquipmentType::WEAPON:
		break;
	case EEquipmentType::BACKPACK: StaticMeshArray[(uint8)EStaticMeshPartsType::E_BACKPACK]->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh))); break;
	case EEquipmentType::FACE: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_FACE]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HAIR: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_HAIR]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::GLOVE: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_GLOVE]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BODY: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOE: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_SHOE]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HEADGEARS: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOULDERPAD: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BELT: SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_BELT]->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	default:
		break;
	}

	OnEquipmentUpdated.Broadcast();
}

UEquipment* UEquipmentComponent::CreateEquipment(int index)
{
	UEquipment* NewEquipment = NewObject<UEquipment>();
	NewEquipment->Init(index, GetWorld());

	return NewEquipment;
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
