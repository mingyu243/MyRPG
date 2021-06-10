#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	NO_WEAPON,
	SWORD_SHIELD,
	TWO_HAND_SWORD,
	BOW,
	DOUBLE_SWORD,
	MAGIC_WAND
};

UCLASS()
class MYRPG_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void BeginPlay() override;

public:
	class UStaticMesh* GetWeaponMesh();
	EWeaponType GetWeaponType();

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	EWeaponType WeaponType;
};
