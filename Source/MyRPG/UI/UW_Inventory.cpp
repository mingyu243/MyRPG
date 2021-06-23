#include "UW_Inventory.h"

#include "UW_InventorySlot.h"
#include "../Unit/Player/Player_Base.h"
#include "../Component/InventoryComponent.h"

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

	// 임의로 얻기보다는 바인딩하는 게 좋을 것 같다!
	// Cast<APlayer_Base>(GetOwningPlayerPawn())->GetInventoryComponent()->OnInventoryUpdated.AddDynamic(this, &UUW_Inventory::RefreshInventory);
}

void UUW_Inventory::BindInventory(UInventoryComponent* Inventory)
{
	if (Inventory == nullptr) return;
	CurrentInventory = Inventory;

	CurrentInventory->OnInventoryUpdated.AddDynamic(this, &UUW_Inventory::RefreshInventory);
}

//void UUW_PlayerStat::BindCharacterStat(UCharacterStatComponent* CharacterStat)
//{
//	if (CharacterStat == nullptr) return;
//	CurrentCharacterStat = CharacterStat;
//	UpdateCharacterStat();
//
//	CharacterStat->OnHPChanged.AddUObject(this, &UUW_PlayerStat::UpdateCharacterStat);
//}

void UUW_Inventory::InitializeInventory()
{

}

void UUW_Inventory::RefreshInventory()
{

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
