#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Inventory.generated.h"

UCLASS()
class MYRPG_API UUW_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UserWidget은 기본 클래스 생성자를 못 쓰나봄. 오류 남.
	virtual void NativeConstruct() override;

public:
	void BindInventory(class UInventoryComponent* Inventory);

	void InitializeInventory(class UInventoryComponent* Inventory);

	UFUNCTION()
	void RefreshInventory();

private:
	UPROPERTY(Meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel;

	int32 SlotMaxCount; // 최대 슬롯 갯수.
	int32 SlotMaxRowCount; // 한 줄에 몇 개 들어갈지.

	TSubclassOf<class UUW_InventorySlot> SlotClass;
	TArray<class UUW_InventorySlot*> SlotList;

	class UInventoryComponent* CurrentInventory;

private:
	void CreateSlot();
};
