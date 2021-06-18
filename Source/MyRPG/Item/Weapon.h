#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Weapon.generated.h"

UCLASS()
class MYRPG_API AWeapon : public AEquipment
{
	GENERATED_BODY()
	
public:
	virtual void Init(int32 index) override;
	virtual void Use() override;

public:
	struct FWeaponData* GetWeaponData();

private:
	struct FWeaponData* CurrentWeaponData;
};
