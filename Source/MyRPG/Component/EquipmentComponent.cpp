#include "EquipmentComponent.h"

#include "../Item/Weapon.h"
#include "../MyGameInstance.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

UEquipmentComponent::UEquipmentComponent()
{


	// Create Skeletal Parts.
	int32 Length = (uint8)ESkeletalMeshPartsType::E_ELEMENT_COUNT;
	SkeletalEquipmentArray.Reserve(Length);
	SkeletalMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		SkeletalEquipmentArray.Add(nullptr); 
		
		FName name = *FString::Printf(TEXT("Sekeltal %i"), i);
		SkeletalMeshArray.Add(CreateDefaultSubobject<USkeletalMeshComponent>(name));
	}

	// Create Static Parts.
	Length = (uint8)EStaticMeshPartsType::E_ELEMENT_COUNT;
	StaticEquipmentArray.Reserve(Length);
	StaticMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		StaticEquipmentArray.Add(nullptr);

		FName name = *FString::Printf(TEXT("Static %i"), i);
		StaticMeshArray.Add(CreateDefaultSubobject<UStaticMeshComponent>(name));
	}

	// 아무것도 안 입었을 때, 기본 착장.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Body(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Cloth02SK.Cloth02SK'"));
	if (SK_Body.Succeeded()) BasicBody = SK_Body.Object;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Face(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Face01SK.Face01SK'"));
	if (SK_Face.Succeeded()) BasicFace = SK_Face.Object;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Hair(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Hair02SK.Hair02SK'"));
	if (SK_Hair.Succeeded()) BasicHair = SK_Hair.Object;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Shoe(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Shoe01SK.Shoe01SK'"));
	if (SK_Shoe.Succeeded()) BasicShoe = SK_Shoe.Object;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Glove(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/ModularBodyParts/Glove01SK.Glove01SK'"));
	if (SK_Glove.Succeeded()) BasicGlove = SK_Glove.Object;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::Init(USkeletalMeshComponent* BodyMesh)
{
	// 기준이 되는 BodyMesh를 설정.
	SkeletalMeshArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH] = BodyMesh;

	// BodyMesh에 MeshComponent들을 Attach 한다.
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

	GetMeshComponent(EStaticMeshPartsType::E_SHIELD)->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_lSocket"));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));
	GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Backpack"));

	GetMeshComponent(EStaticMeshPartsType::E_SHIELD)->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetRelativeLocationAndRotation(FVector(11.0f, -1.8f, -1.5f), FRotator(0.0f, 0.0f, 90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, 0.0f, -90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetRelativeLocationAndRotation(FVector(0.0f, -4.0f, -6.4f), FRotator(0.0f, 0.0f, -3.0f));

	GetMeshComponent(ESkeletalMeshPartsType::E_BODYMESH)->SetSkeletalMesh(BasicBody);
	GetMeshComponent(ESkeletalMeshPartsType::E_FACE)->SetSkeletalMesh(BasicFace);
	GetMeshComponent(ESkeletalMeshPartsType::E_HAIR)->SetSkeletalMesh(BasicHair);
	GetMeshComponent(ESkeletalMeshPartsType::E_SHOE)->SetSkeletalMesh(BasicShoe);
	GetMeshComponent(ESkeletalMeshPartsType::E_GLOVE)->SetSkeletalMesh(BasicGlove);
}

UEquipment* UEquipmentComponent::SetEquipment(UEquipment* Equipment)
{
	UEquipment* ReturnEquipment = nullptr;

	EEquipmentType Type = Equipment->GetEquipmentData()->Enum_EquipmentType;
	
	USkeletalMesh* LoadedMesh_Skeletal = LoadObject<USkeletalMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh));
	switch (Type)
	{
	case EEquipmentType::WEAPON:
	{
		UWeapon* Weapon = Cast<UWeapon>(Equipment);
		Weapon->Init(Equipment->CurrnetIndex, GetWorld());

		SetWeapon(Weapon);
		break;
	}
	case EEquipmentType::BACKPACK: 
		if (StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_BACKPACK] != nullptr) ReturnEquipment = PopEquipment(StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_BACKPACK]); // 이미 있다면, 
		StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_BACKPACK] = Equipment;
		GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh)));
		break;
	case EEquipmentType::FACE:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_FACE] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_FACE]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_FACE] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_FACE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HAIR:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HAIR] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HAIR]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HAIR] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_HAIR)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::GLOVE:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_GLOVE] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_GLOVE]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_GLOVE] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_GLOVE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BODY:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_BODYMESH)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOE:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOE] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOE]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOE] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HEADGEARS:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_HEADGEARS)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOULDERPAD:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOULDERPAD)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BELT:
		if (SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BELT] != nullptr) ReturnEquipment = PopEquipment(SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BELT]);
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BELT] = Equipment;
		GetMeshComponent(ESkeletalMeshPartsType::E_BELT)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	default:
		break;
	}

	// UEquipment 데이터만 바꾸고, SetMesh는 데이터가 바뀔 때, 모든 장비 정보에 대해 메쉬를 다시 설정하는 게 나을 듯.. 성능 차이는 별로 안날 듯.ㅇㄴ;; 고칠 게 많다.
	OnEquipmentUpdated.Broadcast(); 

	return ReturnEquipment;
}

UEquipment* UEquipmentComponent::CreateEquipment(int index)
{
	UEquipment* NewEquipment = NewObject<UEquipment>();
	NewEquipment->Init(index, GetWorld());

	return NewEquipment;
}

USkeletalMeshComponent* UEquipmentComponent::GetMeshComponent(ESkeletalMeshPartsType SK_Type)
{
	return SkeletalMeshArray[(uint8)SK_Type];
}

UStaticMeshComponent* UEquipmentComponent::GetMeshComponent(EStaticMeshPartsType SM_Type)
{
	return StaticMeshArray[(uint8)SM_Type];
}

UEquipment* UEquipmentComponent::GetEquipment(ESkeletalMeshPartsType SK_Type)
{
	return SkeletalEquipmentArray[(uint8)SK_Type];
}

UEquipment* UEquipmentComponent::GetEquipment(EStaticMeshPartsType SM_Type)
{
	return StaticEquipmentArray[(uint8)SM_Type];
}

UEquipment* UEquipmentComponent::PopEquipment(UEquipment* Equipment)
{
	UEquipment* Pop = nullptr;

	EEquipmentType Type = Equipment->GetEquipmentData()->Enum_EquipmentType;
	switch (Type)
	{
	case EEquipmentType::WEAPON:
	{

	}
	case EEquipmentType::BACKPACK:
		Pop = StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_BACKPACK];
		StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_BACKPACK] = nullptr;
		GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetStaticMesh(nullptr); break;
	case EEquipmentType::FACE:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_FACE];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_FACE] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_FACE)->SetSkeletalMesh(BasicFace); break;
	case EEquipmentType::HAIR:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HAIR];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HAIR] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_HAIR)->SetSkeletalMesh(BasicHair); break;
	case EEquipmentType::GLOVE:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_GLOVE];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_GLOVE] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_GLOVE)->SetSkeletalMesh(BasicGlove); break;
	case EEquipmentType::BODY:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BODYMESH] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_BODYMESH)->SetSkeletalMesh(BasicBody); break;
	case EEquipmentType::SHOE:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOE];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOE] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOE)->SetSkeletalMesh(BasicShoe); break;
	case EEquipmentType::HEADGEARS:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_HEADGEARS] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_HEADGEARS)->SetSkeletalMesh(nullptr); break;
	case EEquipmentType::SHOULDERPAD:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_SHOULDERPAD] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOULDERPAD)->SetSkeletalMesh(nullptr); break;
	case EEquipmentType::BELT:
		Pop = SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BELT];
		SkeletalEquipmentArray[(uint8)ESkeletalMeshPartsType::E_BELT] = nullptr;
		GetMeshComponent(ESkeletalMeshPartsType::E_BELT)->SetSkeletalMesh(nullptr); break;
	default:
		break;
	}

	return Pop;
}

UWeapon* UEquipmentComponent::CreateWeapon(int index)
{
	UWeapon* NewWeapon = NewObject<UWeapon>();
	NewWeapon->Init(index, GetWorld());

	return NewWeapon;
}

UWeapon* UEquipmentComponent::GetWeapon()
{
	return nullptr;
}

void UEquipmentComponent::SetWeapon(UWeapon* NewWeapon)
{
	EWeaponType Type = NewWeapon->GetWeaponData()->Enum_WeaponType;
	switch (Type)
	{
	case EWeaponType::SWORD:
	{
		UEquipment* WeaponL = StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_LEFT];
		if (WeaponL)
		{
			StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_RIGHT] = NewWeapon;
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(NewWeapon->GetItemData()->Path_Mesh))); break;
		}
		else
		{
			StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_LEFT] = NewWeapon;
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(NewWeapon->GetItemData()->Path_Mesh))); break;
		}
		break;
	}
	case EWeaponType::SHIELD:
	{
		UEquipment* WeaponR = StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_RIGHT];
		if (WeaponR)
		{
			StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_RIGHT] = NewWeapon;
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(NewWeapon->GetItemData()->Path_Mesh))); break;
		}
		else
		{
			StaticEquipmentArray[(uint8)EStaticMeshPartsType::E_WEAPON_LEFT] = NewWeapon;
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(NewWeapon->GetItemData()->Path_Mesh))); break;
		}
		break;
	}
	case EWeaponType::BOW:
		break;
	case EWeaponType::MAGIC_WAND:
		break;
	case EWeaponType::AXE:
		break;
	case EWeaponType::HAMMER:
		break;
	default:
		break;
	}

	OnEquipmentUpdated.Broadcast();
	OnWeaponUpdated.Broadcast();
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
