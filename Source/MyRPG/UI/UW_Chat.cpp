#include "UW_Chat.h"

#include "../Main/Main_PC.h"

#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UUW_Chat::NativeConstruct()
{
	Super::NativeConstruct();

	ChatInputText->OnTextCommitted.AddDynamic(this, &UUW_Chat::OnChatTextCommitted);
}

void UUW_Chat::AddChatMessage(const FString& Message)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatHistoryArea);
	NewTextBlock->SetText(FText::FromString(Message));

	ChatHistoryArea->AddChild(NewTextBlock);
	ChatHistoryArea->ScrollToEnd();
}

void UUW_Chat::SetChatInputTextMessage(const FText& Text)
{
	ChatInputText->SetText(Text);
}

FText UUW_Chat::GetChatInputTextMessage()
{
	return ChatInputText->GetText();
}

TSharedPtr<SWidget> UUW_Chat::GetChatInputText()
{
	return ChatInputText->GetCachedWidget();
}

void UUW_Chat::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	AMain_PC* MyPC = Cast<AMain_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyPC == nullptr) return;



	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (Text.IsEmpty() == false)
		{
			MyPC->SendMessage(Text);
			SetChatInputTextMessage(FText::GetEmpty());
		}
		MyPC->FocusGame();
		break;
	case ETextCommit::OnCleared:
		MyPC->FocusGame();
		break;
	}
}
