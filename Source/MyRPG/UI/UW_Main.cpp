#include "UW_Main.h"

#include "UW_Chat.h"

TSharedPtr<SWidget> UUW_Main::GetChatInputText()
{
	return WB_Chat->GetChatInputText();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}
