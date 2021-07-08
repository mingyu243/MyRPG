#include "UW_Main.h"

#include "UW_Chat.h"
#include "UW_PlayerStat.h"
#include "UW_Inventory.h"
#include "UW_Equipment.h"

void UUW_Main::NativeConstruct()
{
	Super::NativeConstruct();

	ShowInventory(false);
	ShowEquipment(false);
}

TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return WB_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}

void UUW_Main::ShowInventory(bool bIsShow)
{
	WB_Inventory->SetVisibility(bIsShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UUW_Main::ShowEquipment(bool bIsShow)
{
	WB_Equipment->SetVisibility(bIsShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UUW_Main::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	WB_PlayerStat->BindCharacterStat(CharacterStat);
}

void UUW_Main::BindInventory(UInventoryComponent* Inventory)
{
	WB_Inventory->BindInventory(Inventory);
}

void UUW_Main::BindEquipment(UEquipmentComponent* Equipment)
{
	WB_Equipment->BindEquipmentComponent(Equipment);
}
