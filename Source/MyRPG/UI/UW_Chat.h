#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Chat.generated.h"

UCLASS()
class MYRPG_API UUW_Chat : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
public:
	void AddChatMessage(const FString& Message);
	void SetChatInputTextMessage(const FText& Text);
	FText GetChatInputTextMessage();
	TSharedPtr<class SWidget> GetChatInputText();

private:
	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* ChatHistoryArea;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* ChatInputText;

private:
	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
