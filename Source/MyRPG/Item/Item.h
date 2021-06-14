#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYRPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void BeginPlay() override;

public:
	virtual void Use();

public:
	struct FItemData* GetItemData();

private:
	struct FItemData* CurrentItemData;
};
