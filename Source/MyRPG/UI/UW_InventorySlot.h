#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_InventorySlot.generated.h"

UCLASS()
class MYRPG_API UUW_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItem(class UItem* Item);
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Slot;
	UPROPERTY(Meta = (BindWidget))
	class UImage* Image_ItemIcon;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_ItemCount;

private:
	class UItem* CurrentItem;

private:
	void SetItemIconImage(class UTexture2D* Texture);
	void SetItemCountText(const FText& Text);
};
