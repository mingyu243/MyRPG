#include "UW_Main.h"

#include "UW_Chat.h"

TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return WB_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}
