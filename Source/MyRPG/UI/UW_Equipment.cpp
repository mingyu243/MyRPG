#include "UW_Equipment.h"

#include "UW_EquipmentSlot.h"
#include "../Component/EquipmentComponent.h"
#include "../Item/Equipment.h"

void UUW_Equipment::NativeConstruct()
{
	Super::NativeConstruct();

	WB_EquipmentSlot_HeadGears->SetTypeText(FText::FromString(TEXT("HeadGears")));
	WB_EquipmentSlot_Hair->SetTypeText(FText::FromString(TEXT("Hair")));
	WB_EquipmentSlot_Face->SetTypeText(FText::FromString(TEXT("Face")));
	WB_EquipmentSlot_ShoulderPad->SetTypeText(FText::FromString(TEXT("ShoulderPad")));
	WB_EquipmentSlot_Body->SetTypeText(FText::FromString(TEXT("Body")));
	WB_EquipmentSlot_Backpack->SetTypeText(FText::FromString(TEXT("Backpack")));
	WB_EquipmentSlot_Belt->SetTypeText(FText::FromString(TEXT("Belt")));
	WB_EquipmentSlot_Glove->SetTypeText(FText::FromString(TEXT("Glove")));
	WB_EquipmentSlot_Shoe->SetTypeText(FText::FromString(TEXT("Shoe")));

	WB_EquipmentSlot_WeaponL->SetTypeText(FText::FromString(TEXT("WeaponL")));
	WB_EquipmentSlot_WeaponR->SetTypeText(FText::FromString(TEXT("WeaponR")));
}

void UUW_Equipment::BindEquipmentComponent(UEquipmentComponent* EquipmentComponent)
{
	if (EquipmentComponent == nullptr) return;
	CurrentEquipmentComponent = EquipmentComponent;

	CurrentEquipmentComponent->OnEquipmentUpdated.AddDynamic(this, &UUW_Equipment::RefreshEquipment);
}

void UUW_Equipment::InitializeEquipment(UEquipmentComponent* EquipmentComponent)
{
	WB_EquipmentSlot_HeadGears->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_HEADGEARS));
	WB_EquipmentSlot_HeadGears->PartsType = EAllMeshPartsType::E_HEADGEARS;
	WB_EquipmentSlot_Hair->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_HAIR));
	WB_EquipmentSlot_Hair->PartsType = EAllMeshPartsType::E_HAIR;
	WB_EquipmentSlot_Face->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_FACE));
	WB_EquipmentSlot_Face->PartsType = EAllMeshPartsType::E_FACE;
	WB_EquipmentSlot_ShoulderPad->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_SHOULDERPAD));
	WB_EquipmentSlot_ShoulderPad->PartsType = EAllMeshPartsType::E_SHOULDERPAD;
	WB_EquipmentSlot_Body->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_BODYMESH));
	WB_EquipmentSlot_Body->PartsType = EAllMeshPartsType::E_BODYMESH;
	WB_EquipmentSlot_Belt->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_BELT));
	WB_EquipmentSlot_Belt->PartsType = EAllMeshPartsType::E_BELT;
	WB_EquipmentSlot_Shoe->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_SHOE));
	WB_EquipmentSlot_Shoe->PartsType = EAllMeshPartsType::E_SHOE;
	WB_EquipmentSlot_Glove->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_GLOVE));
	WB_EquipmentSlot_Glove->PartsType = EAllMeshPartsType::E_GLOVE;

	WB_EquipmentSlot_Backpack->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_BACKPACK));
	WB_EquipmentSlot_Backpack->PartsType = EAllMeshPartsType::E_BACKPACK;

	WB_EquipmentSlot_WeaponL->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_LEFT));
	WB_EquipmentSlot_WeaponL->PartsType = EAllMeshPartsType::E_WEAPON_LEFT;
	WB_EquipmentSlot_WeaponR->SetEquipment(EquipmentComponent->GetEquipmentInfo(EAllMeshPartsType::E_WEAPON_RIGHT));
	WB_EquipmentSlot_WeaponR->PartsType = EAllMeshPartsType::E_WEAPON_RIGHT;

	// UI 초기화 해줄랬는데, 
	// EquipmentComponent에 SkeletalMeshComponent만 있고,
	// UEquipment 데이터는 안 들고 있었음.. ㄷㄷ;;
	// Enum에 값 넣어서 배열로 처리 해줘야 코드가 깔끔해질 것 같음.
}

void UUW_Equipment::RefreshEquipment()
{
	InitializeEquipment(CurrentEquipmentComponent);
}
