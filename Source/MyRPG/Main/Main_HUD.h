#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Main_HUD.generated.h"

UCLASS()
class MYRPG_API AMain_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMain_HUD();
	virtual void BeginPlay() override;

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);
	void ToggleInventory(bool isShow);
	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);
	void BindInventory(class UInventoryComponent* Inventory);

private:
	TSubclassOf<class UUW_Main> MainUIClass;
	class UUW_Main* MainUIObject;

	TSubclassOf<class UUW_Inventory> InventoryUIClass;
	class UUW_Inventory* InventoryUIObject;

private:
	template <typename T_UMGClass>
	bool CreateUIObject(TSubclassOf<T_UMGClass> UIClass, T_UMGClass** UIObject);
};