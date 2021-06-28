#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Weapon.generated.h"

UCLASS()
class MYRPG_API UWeapon : public UEquipment
{
	GENERATED_BODY()
	
public:
	virtual void Init(int32 index, UWorld* CurrentWorld) override;
	virtual void Use(class APlayer_Base* Character) override;

public:
	struct FWeaponData* GetWeaponData();

private:
	struct FWeaponData* CurrentWeaponData;
};
