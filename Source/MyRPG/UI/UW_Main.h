#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Main.generated.h"

UCLASS()
class MYRPG_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()
	
public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UUW_Chat* WB_Chat;
};
