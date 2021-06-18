#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Equipment.generated.h"

UCLASS()
class MYRPG_API AEquipment : public AItem
{
	GENERATED_BODY()
	
public:
	virtual void Init(int32 index) override;
	virtual void Use() override;

public:
	struct FEquipmentData* GetEquipmentData();

private:
	struct FEquipmentData* CurrentEquipmentData;
};
