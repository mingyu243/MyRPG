#include "UW_EquipmentSlot.h"

#include "../Unit/Player/Player_Base.h"
#include "../Item/Equipment.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUW_EquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Slot->OnClicked.AddDynamic(this, &UUW_EquipmentSlot::SlotClicked);
}

void UUW_EquipmentSlot::SetEquipment(UEquipment* Equipment)
{
	CurrentEquipment = Equipment;
	if (CurrentEquipment != nullptr && CurrentEquipment->GetItemData() != nullptr)
	{
		SetItemIconImage(LoadObject<UTexture2D>(NULL, *(CurrentEquipment->GetItemData()->Path_Icon)));
	}
	else
	{
		SetItemIconImage(nullptr);
	}
}

void UUW_EquipmentSlot::SlotClicked()
{
	APlayer_Base* Player = Cast<APlayer_Base>(GetOwningPlayerPawn());
	if (Player)
	{
		if (Player->TakeOffEquipment(CurrentEquipment, PartsType) == true)
		{
			SetEquipment(nullptr);
		}
	}
}

void UUW_EquipmentSlot::SetItemIconImage(UTexture2D* Texture)
{
	Image_ItemIcon->SetBrushFromTexture(Texture);
}

void UUW_EquipmentSlot::SetTypeText(const FText& Text)
{
	Text_Type->SetText(Text);
}
