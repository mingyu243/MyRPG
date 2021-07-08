#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../CustomDataTables.h"
#include "EquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class ESkeletalMeshPartsType : uint8
{
	E_HEADGEARS = 0,
	E_HAIR = 1,
	E_FACE = 2,
	E_SHOULDERPAD = 3,
	E_BODYMESH = 4,
	E_BELT = 5,
	E_GLOVE = 6,
	E_SHOE = 7,
	E_ELEMENT_COUNT = 8
};

UENUM(BlueprintType)
enum class EStaticMeshPartsType : uint8
{
	E_BACKPACK = 0,
	E_SHIELD = 1,
	E_WEAPON_LEFT = 2,
	E_WEAPON_RIGHT = 3,
	E_ELEMENT_COUNT = 4
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();
	virtual void BeginPlay() override;

public:
	void Init(class USkeletalMeshComponent* NewBodyMesh);
	void SetEquipment(class UEquipment* Equipment);
	class UEquipment* CreateEquipment(int index);
	class USkeletalMeshComponent* GetMeshComponent(ESkeletalMeshPartsType SK_Type);
	class UStaticMeshComponent* GetMeshComponent(EStaticMeshPartsType SM_Type);
	class UEquipment* GetEquipment(ESkeletalMeshPartsType SK_Type);
	class UEquipment* GetEquipment(EStaticMeshPartsType SM_Type);
	class UEquipment* PopEquipment(class UEquipment* Equipment);

	TArray<class UEquipment*>& GetSkeletalEquipments()
	{
		return SkeletalEquipmentArray;
	}
	TArray<class UEquipment*>& GetStaticEquipments()
	{
		return StaticEquipmentArray;
	}

	class UWeapon* CreateWeapon(int index);
	class UWeapon* GetWeapon();
	void SetWeapon(class UWeapon* NewWeapon);

public:
	UPROPERTY(VisibleAnywhere)
	FOnEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY(VisibleAnywhere)
	FOnWeaponUpdated OnWeaponUpdated;

public:
	// 애니메이션으로 움직이는 메쉬들.
	TArray<UEquipment*> SkeletalEquipmentArray;
	TArray<UEquipment*> StaticEquipmentArray;

	// 부착되는 메쉬들.
	TArray<USkeletalMeshComponent*> SkeletalMeshArray;
	TArray<UStaticMeshComponent*> StaticMeshArray;

	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* BasicBody;
	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* BasicFace;
	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* BasicHair;
	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* BasicShoe;
	UPROPERTY(VisibleAnywhere)
	USkeletalMesh* BasicGlove;

	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* HeadGears;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* Hair;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* Face;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* ShoulderPad;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* BodyMesh;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* Belt;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* Glove;
	//UPROPERTY(VisibleAnywhere)
	//class USkeletalMeshComponent* Shoe;

	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* Backpack;
	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* Shield;
	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* WeaponR;
	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* WeaponL;

	//UPROPERTY(VisibleAnywhere)
	//class AWeapon* CurrentWeapon;
};
