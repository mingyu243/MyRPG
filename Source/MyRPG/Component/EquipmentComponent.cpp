#include "EquipmentComponent.h"

#include "../Item/Weapon.h"
#include "../MyGameInstance.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

UEquipmentComponent::UEquipmentComponent()
{
	// 장비 정보를 담는 배열.
	int32 Length = (uint8)EAllMeshPartsType::E_ELEMENT_COUNT;
	EquipmentArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		EquipmentArray.Add(nullptr);
	}

	// 장비에 따라 Skeletal Mesh, Static Mesh 로 구분되어있어서, 개수만큼 따로 배열을 만들어준다.
	Length = (uint8)ESkeletalMeshPartsType::E_ELEMENT_COUNT;
	SkeletalMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		SkeletalMeshArray.Add(CreateDefaultSubobject<USkeletalMeshComponent>(*FString::Printf(TEXT("Sekeltal %i"), i)));
	}
	Length = (uint8)EStaticMeshPartsType::E_ELEMENT_COUNT;
	StaticMeshArray.Reserve(Length);
	for (int i = 0; i < Length; i++)
	{
		StaticMeshArray.Add(CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("Static %i"), i)));
	}

	GetMeshComponent(EStaticMeshPartsType::E_SHIELD)->SetRelativeLocationAndRotation(FVector(16.0f, 0.5f, -2.0f), FRotator(0.0f, -18.0f, 90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetRelativeLocationAndRotation(FVector(11.0f, -1.8f, -1.5f), FRotator(0.0f, 0.0f, 90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetRelativeLocationAndRotation(FVector(-11.0f, 2.17f, 2.0f), FRotator(0.0f, 0.0f, -90.0f));
	GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetRelativeLocationAndRotation(FVector(0.0f, -4.0f, -6.4f), FRotator(0.0f, 0.0f, -3.0f));

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
		switch (Weapon->GetWeaponData()->Enum_WeaponType)
		{
		case EWeaponType::SWORD:
		{
			UEquipment* WeaponR = GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_RIGHT);
			if (WeaponR)
			{
				UEquipment* WeaponL = GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT);
				if (WeaponL)
				{
					ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT), EAllMeshPartsType::E_WEAPON_LEFT);
				}
				SetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT, Weapon);
				GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Weapon->GetItemData()->Path_Mesh)));
			}
			else
			{
				SetEquipmentInfo(EAllMeshPartsType::E_WEAPON_RIGHT, Weapon);
				GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Weapon->GetItemData()->Path_Mesh)));
			}
			break;
		}
		case EWeaponType::SHIELD:
		{
			UEquipment* WeaponL = GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT);
			if (WeaponL)
			{
				ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT), EAllMeshPartsType::E_WEAPON_LEFT);
			}
			SetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT, Weapon);
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Weapon->GetItemData()->Path_Mesh)));
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
		UE_LOG(LogClass, Warning, TEXT("111"));
		OnWeaponUpdated.Broadcast(GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT), GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_RIGHT));
		break;
	}
	case EEquipmentType::BACKPACK: 
		if (GetEquipmentInfo(EAllMeshPartsType::E_BACKPACK) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_BACKPACK), EAllMeshPartsType::E_BACKPACK); // 이미 있다면, 
		SetEquipmentInfo(EAllMeshPartsType::E_BACKPACK, Equipment);
		GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *(Equipment->GetItemData()->Path_Mesh)));
		break;
	case EEquipmentType::FACE:
		if (GetEquipmentInfo(EAllMeshPartsType::E_FACE) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_FACE), EAllMeshPartsType::E_FACE);
		SetEquipmentInfo(EAllMeshPartsType::E_FACE, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_FACE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HAIR:
		if (GetEquipmentInfo(EAllMeshPartsType::E_HAIR) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_HAIR), EAllMeshPartsType::E_HAIR);
		SetEquipmentInfo(EAllMeshPartsType::E_HAIR, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_HAIR)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::GLOVE:
		if (GetEquipmentInfo(EAllMeshPartsType::E_GLOVE) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_GLOVE), EAllMeshPartsType::E_GLOVE);
		SetEquipmentInfo(EAllMeshPartsType::E_GLOVE, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_GLOVE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BODY:
		if (GetEquipmentInfo(EAllMeshPartsType::E_BODYMESH) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_BODYMESH), EAllMeshPartsType::E_BODYMESH);
		SetEquipmentInfo(EAllMeshPartsType::E_BODYMESH, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_BODYMESH)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOE:
		if (GetEquipmentInfo(EAllMeshPartsType::E_SHOE) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_SHOE), EAllMeshPartsType::E_SHOE);
		SetEquipmentInfo(EAllMeshPartsType::E_SHOE, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOE)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::HEADGEARS:
		if (GetEquipmentInfo(EAllMeshPartsType::E_HEADGEARS) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_HEADGEARS), EAllMeshPartsType::E_HEADGEARS);
		SetEquipmentInfo(EAllMeshPartsType::E_HEADGEARS, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_HEADGEARS)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::SHOULDERPAD:
		if (GetEquipmentInfo(EAllMeshPartsType::E_SHOULDERPAD) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_SHOULDERPAD), EAllMeshPartsType::E_SHOULDERPAD);
		SetEquipmentInfo(EAllMeshPartsType::E_SHOULDERPAD, Equipment);
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOULDERPAD)->SetSkeletalMesh(LoadedMesh_Skeletal); break;
	case EEquipmentType::BELT:
		if (GetEquipmentInfo(EAllMeshPartsType::E_BELT) != nullptr) ReturnEquipment = PopEquipment(GetEquipmentInfo(EAllMeshPartsType::E_BELT), EAllMeshPartsType::E_BELT);
		SetEquipmentInfo(EAllMeshPartsType::E_BELT, Equipment);
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

UEquipment* UEquipmentComponent::GetEquipmentInfo(EAllMeshPartsType Type)
{
	return EquipmentArray[(uint8)Type];
}
void UEquipmentComponent::SetEquipmentInfo(EAllMeshPartsType Type, UEquipment* NewEquipment)
{
	EquipmentArray[(uint8)Type] = NewEquipment;
}

UEquipment* UEquipmentComponent::PopEquipment(UEquipment* Equipment, EAllMeshPartsType PartsType)
{
	EEquipmentType Type = Equipment->GetEquipmentData()->Enum_EquipmentType;

	UEquipment* Pop = GetEquipmentInfo(PartsType);
	SetEquipmentInfo(PartsType, nullptr);

	switch (Type)
	{
	case EEquipmentType::WEAPON:
		switch (PartsType)
		{
		case EAllMeshPartsType::E_WEAPON_LEFT:
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_LEFT)->SetStaticMesh(nullptr); break;
		case EAllMeshPartsType::E_WEAPON_RIGHT:
			GetMeshComponent(EStaticMeshPartsType::E_WEAPON_RIGHT)->SetStaticMesh(nullptr); break;
		default:
			break;
		}
		break;
	case EEquipmentType::BACKPACK:
		GetMeshComponent(EStaticMeshPartsType::E_BACKPACK)->SetStaticMesh(nullptr); break;
	case EEquipmentType::FACE:
		GetMeshComponent(ESkeletalMeshPartsType::E_FACE)->SetSkeletalMesh(BasicFace); break;
	case EEquipmentType::HAIR:
		GetMeshComponent(ESkeletalMeshPartsType::E_HAIR)->SetSkeletalMesh(BasicHair); break;
	case EEquipmentType::GLOVE:
		GetMeshComponent(ESkeletalMeshPartsType::E_GLOVE)->SetSkeletalMesh(BasicGlove); break;
	case EEquipmentType::BODY:
		GetMeshComponent(ESkeletalMeshPartsType::E_BODYMESH)->SetSkeletalMesh(BasicBody); break;
	case EEquipmentType::SHOE:
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOE)->SetSkeletalMesh(BasicShoe); break;
	case EEquipmentType::HEADGEARS:
		GetMeshComponent(ESkeletalMeshPartsType::E_HEADGEARS)->SetSkeletalMesh(nullptr); break;
	case EEquipmentType::SHOULDERPAD:
		GetMeshComponent(ESkeletalMeshPartsType::E_SHOULDERPAD)->SetSkeletalMesh(nullptr); break;
	case EEquipmentType::BELT:
		GetMeshComponent(ESkeletalMeshPartsType::E_BELT)->SetSkeletalMesh(nullptr); break;
	default:
		break;
	}

	OnEquipmentUpdated.Broadcast();
	OnWeaponUpdated.Broadcast(GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT), GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_RIGHT));

	return Pop;
}

UWeapon* UEquipmentComponent::CreateWeapon(int index)
{
	UWeapon* NewWeapon = NewObject<UWeapon>();
	NewWeapon->Init(index, GetWorld());

	return NewWeapon;
}
