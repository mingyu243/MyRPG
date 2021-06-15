#include "UW_Main.h"

#include "UW_Chat.h"
#include "UW_PlayerStat.h"

TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return WB_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}

void UUW_Main::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	WB_PlayerStat->BindCharacterStat(CharacterStat);
}
