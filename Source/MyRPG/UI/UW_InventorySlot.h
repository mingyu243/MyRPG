#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_InventorySlot.generated.h"

UCLASS()
class MYRPG_API UUW_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Slot;
	UPROPERTY(Meta = (BindWidget))
	class UImage* Image_ItemIcon;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_ItemCount;
};
