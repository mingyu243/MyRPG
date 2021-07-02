#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_EquipmentSlot.generated.h"

UCLASS()
class MYRPG_API UUW_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	void SetEquipment(class UEquipment* Equipment);
	void SetTypeText(const FText& Text);

private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* Text_Type;
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Slot;
	UPROPERTY(Meta = (BindWidget))
	class UImage* Image_ItemIcon;

private:
	class UEquipment* CurrentEquipment;

private:
	UFUNCTION()
	void TakeOffEquipment();

	void SetItemIconImage(class UTexture2D* Texture);
};
