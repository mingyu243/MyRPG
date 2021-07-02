#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Equipment.generated.h"

UCLASS()
class MYRPG_API UUW_Equipment : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
public:
	void BindEquipmentComponent(class UEquipmentComponent* EquipmentComponent);

	void InitializeEquipment(class UEquipmentComponent* EquipmentComponent);

	UFUNCTION()
	void RefreshEquipment();

private:
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_HeadGears;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Hair;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Face;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_ShoulderPad;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Body;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Backpack;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Belt;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Glove;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_Shoe;

	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_WeaponL;
	UPROPERTY(Meta = (BindWidget))
	class UUW_EquipmentSlot* WB_EquipmentSlot_WeaponR;


	class UEquipmentComponent* CurrentEquipmentComponent;
};
