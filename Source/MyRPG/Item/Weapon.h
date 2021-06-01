#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MYRPG_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WeaponMesh;
};
