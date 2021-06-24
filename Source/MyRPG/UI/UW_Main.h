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
	virtual void NativeConstruct() override;
	
public:
	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);
	void BindInventory(class UInventoryComponent* Inventory);

public:
	TSharedPtr<SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);

	void ShowInventory(bool bIsShow);

private:
	UPROPERTY(Meta = (BindWidget))
	class UUW_Chat* WB_Chat;
	UPROPERTY(Meta = (BindWidget))
	class UUW_PlayerStat* WB_PlayerStat;
	UPROPERTY(Meta = (BindWidget))
	class UUW_Inventory* WB_Inventory;
};
