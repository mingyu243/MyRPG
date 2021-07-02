#include "UW_Inventory.h"

#include "UW_InventorySlot.h"
#include "../Unit/Player/Player_Base.h"
#include "../Component/InventoryComponent.h"
#include "../Item/Item.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UUW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	
	SlotMaxCount = 10;
	SlotMaxRowCount = 4;

	SlotClass = LoadClass<UUW_InventorySlot>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/UI/WB/WB_InventorySlot.WB_InventorySlot_C'"));
	if (SlotClass)
	{
		CreateSlot();
	}
	UniformGridPanel->SetMinDesiredSlotWidth(128.0f);
	UniformGridPanel->SetMinDesiredSlotHeight(128.0f);

	// 임의로 얻기보다는 바인딩하는 게 좋을 것 같다!
	// Cast<APlayer_Base>(GetOwningPlayerPawn())->GetInventoryComponent()->OnInventoryUpdated.AddDynamic(this, &UUW_Inventory::RefreshInventory);
}

void UUW_Inventory::BindInventory(UInventoryComponent* Inventory)
{
	if (Inventory == nullptr) return;
	CurrentInventory = Inventory;

	CurrentInventory->OnInventoryUpdated.AddDynamic(this, &UUW_Inventory::RefreshInventory);
	InitializeInventory(CurrentInventory);
}

void UUW_Inventory::InitializeInventory(UInventoryComponent* Inventory)
{
	TArray<UItem*> Items = Inventory->GetItems();

	for (int i=0; i<Items.Num(); i++)
	{
		SlotList[i]->SetItem(Items[i]);
		// 아이템만큼 UI 채워놓기.
	}
}

void UUW_Inventory::RefreshInventory()
{
	InitializeInventory(CurrentInventory);
}

void UUW_Inventory::CreateSlot()
{
	int32 CurrentRow = 0;
	int32 CurrentColumn = 0;

	for (int i = 0; i < SlotMaxCount; i++)
	{
		CurrentRow = i / SlotMaxRowCount;
		CurrentColumn = i % SlotMaxRowCount;

		UUW_InventorySlot* NewSlot = CreateWidget<UUW_InventorySlot>(GetOwningPlayer(), SlotClass);

		if (UUniformGridSlot* GridSlot = UniformGridPanel->AddChildToUniformGrid(NewSlot))
		{
			GridSlot->SetRow(CurrentRow);
			GridSlot->SetColumn(CurrentColumn);
			GridSlot->SetHorizontalAlignment(HAlign_Fill);
			GridSlot->SetVerticalAlignment(VAlign_Fill);
		}

		SlotList.Add(NewSlot);
	}
}
