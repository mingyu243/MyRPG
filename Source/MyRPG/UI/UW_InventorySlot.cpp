#include "UW_InventorySlot.h"

#include "../Unit/Player/Player_Base.h"
#include "../Item/Item.h"
#include "../CustomDataTables.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"

void UUW_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Slot->OnClicked.AddDynamic(this, &UUW_InventorySlot::UseItem);
}

void UUW_InventorySlot::SetItem(UItem* Item)
{
	CurrentItem = Item;
	if (CurrentItem)
	{
		SetItemIconImage(LoadObject<UTexture2D>(NULL, *(CurrentItem->GetItemData()->Path_Icon)));
	}
}

void UUW_InventorySlot::UseItem()
{
	APlayer_Base* Player = Cast<APlayer_Base>(GetOwningPlayerPawn());
	if (Player)
	{
		Player->UseItem(CurrentItem);
	}
}

void UUW_InventorySlot::SetItemIconImage(UTexture2D* Texture)
{
	Image_ItemIcon->SetBrushFromTexture(Texture);
}

void UUW_InventorySlot::SetItemCountText(const FText& Text)
{
	Text_ItemCount->SetText(Text);
}
