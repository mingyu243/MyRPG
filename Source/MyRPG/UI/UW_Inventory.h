#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Inventory.generated.h"

UCLASS()
class MYRPG_API UUW_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UserWidget�� �⺻ Ŭ���� �����ڸ� �� ������. ���� ��.
	virtual void NativeConstruct() override;

public:
	void BindInventory(class UInventoryComponent* Inventory);

	void InitializeInventory(class UInventoryComponent* Inventory);

	UFUNCTION()
	void RefreshInventory();

private:
	UPROPERTY(Meta = (BindWidget))
	class UUniformGridPanel* UniformGridPanel;

	int32 SlotMaxCount; // �ִ� ���� ����.
	int32 SlotMaxRowCount; // �� �ٿ� �� �� ����.

	TSubclassOf<class UUW_InventorySlot> SlotClass;
	TArray<class UUW_InventorySlot*> SlotList;

	class UInventoryComponent* CurrentInventory;

private:
	void CreateSlot();
};
