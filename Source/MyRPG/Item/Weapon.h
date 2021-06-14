#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Weapon.generated.h"

UCLASS()
class MYRPG_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void BeginPlay() override;

public:
	struct FWeaponData* GetWeaponData();

private:
	struct FWeaponData* CurrentWeaponData;
};
