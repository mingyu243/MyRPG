#include "UW_Main.h"

#include "UW_Chat.h"
#include "UW_PlayerStat.h"
#include "UW_Inventory.h"

void UUW_Main::NativeConstruct()
{
	Super::NativeConstruct();

	WB_Inventory->SetVisibility(ESlateVisibility::Hidden);
}

TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return WB_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}

bool UUW_Main::isShowInventory()
{
	return (WB_Inventory->GetVisibility() == ESlateVisibility::Visible);
}

void UUW_Main::ShowInventory(bool bIsShow)
{
	WB_Inventory->SetVisibility(bIsShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UUW_Main::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	WB_PlayerStat->BindCharacterStat(CharacterStat);
}

void UUW_Main::BindInventory(class UInventoryComponent* Inventory)
{

}
