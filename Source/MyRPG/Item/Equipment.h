#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Equipment.generated.h"

UCLASS()
class MYRPG_API UEquipment : public UItem
{
	GENERATED_BODY()
	
public:
	virtual void Init(int32 index, UWorld* CurrentWorld) override;
	virtual void Use(class APlayer_Base* Character) override;

public:
	struct FEquipmentData* GetEquipmentData();

private:
	struct FEquipmentData* CurrentEquipmentData;
};
