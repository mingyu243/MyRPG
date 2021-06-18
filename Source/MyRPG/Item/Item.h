#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYRPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void Init(int32 index);
	virtual void Use();

public:
	struct FItemData* GetItemData();

private:
	struct FItemData* CurrentItemData;
};
