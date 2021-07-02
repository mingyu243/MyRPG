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
	// UI �ʱ�ȭ ���ٷ��µ�, 
	// EquipmentComponent�� SkeletalMeshComponent�� �ְ�,
	// UEquipment �����ʹ� �� ��� �־���.. ����;;
	// Enum�� �� �־ �迭�� ó�� ����� �ڵ尡 ������� �� ����.
}

void UUW_Equipment::RefreshEquipment()
{
	InitializeEquipment(CurrentEquipmentComponent);
}
