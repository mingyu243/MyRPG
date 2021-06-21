#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS()
class MYRPG_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual class UWorld* GetWorld() const { return World; };

public:
	virtual void Init(int32 index);
	virtual void Use(class APlayer_Base* Character);

public:
	UPROPERTY(Transient)
	class UWorld* World;
	UPROPERTY()
	class UInventoryComponent* OwningInventory;

public:
	struct FItemData* GetItemData();

private:
	struct FItemData* CurrentItemData;
};
