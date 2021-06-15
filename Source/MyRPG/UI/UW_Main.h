#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Main.generated.h"

// (Main Level¿« ∏ﬁ¿Œ UI)
UCLASS()
class MYRPG_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UUW_Chat* WB_Chat;
	UPROPERTY(Meta = (BindWidget))
	class UUW_PlayerStat* WB_PlayerStat;
};
