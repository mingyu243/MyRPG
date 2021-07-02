#include "UW_Equipment.h"

#include "UW_EquipmentSlot.h"
#include "../Component/EquipmentComponent.h"

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

void UUW_Equipment::InitializeEquipment(UEquipmentComponent* Equipment)
{
	// UI 초기화 해줄랬는데, 
	// EquipmentComponent에 SkeletalMeshComponent만 있고,
	// UEquipment 데이터는 안 들고 있었음.. ㄷㄷ;;
	// Enum에 값 넣어서 배열로 처리 해줘야 코드가 깔끔해질 것 같음.
}

void UUW_Equipment::RefreshEquipment()
{
	InitializeEquipment(CurrentEquipmentComponent);
}
