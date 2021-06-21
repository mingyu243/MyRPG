#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	FOnInventoryUpdated OnInventoryUpdated;

public:
	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<class UItem*> DefaultItems; // 시작할 때 얻을 수 있는 기본 아이템들.

	UPROPERTY(VisibleAnywhere)
	int32 Capacity;

	UPROPERTY(VisibleAnywhere)
	TArray<class UItem*> Items;
};
