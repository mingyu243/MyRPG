#include "UW_Inventory.h"

#include "UW_InventorySlot.h"

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
