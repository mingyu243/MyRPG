#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../CustomDataTables.h"
#include "EquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class EAllMeshPartsType : uint8
{
	// Skeletal
	E_HEADGEARS = 0,
	E_HAIR = 1,
	E_FACE = 2,
	E_SHOULDERPAD = 3,
	E_BODYMESH = 4,
	E_BELT = 5,
	E_GLOVE = 6,
	E_SHOE = 7,

	// Static
	E_BACKPACK = 8,
	E_SHIELD = 9,
	E_WEAPON_LEFT = 10,
	E_WEAPON_RIGHT = 11,
	E_ELEMENT_COUNT = 12
};

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponUpdated, UEquipment*, WeaponL, UEquipment*, WeaponR);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();
	virtual void BeginPlay() override;

public:
	void Init(class USkeletalMeshComponent* NewBodyMesh);
	class UEquipment* SetEquipment(class UEquipment* Equipment); // 아무것도 장착하지 않았다면 장착. 이미 장착하고 있다면 새로운 것을 장착하고, 장착하고 있던 것을 return 함.
	class UEquipment* CreateEquipment(int index);
	class USkeletalMeshComponent* GetMeshComponent(ESkeletalMeshPartsType SK_Type);
	class UStaticMeshComponent* GetMeshComponent(EStaticMeshPartsType SM_Type);
	class UEquipment* GetEquipmentInfo(EAllMeshPartsType Type);
	void SetEquipmentInfo(EAllMeshPartsType Type, class UEquipment* NewEquipment);
	class UEquipment* PopEquipment(class UEquipment* Equipment, EAllMeshPartsType PartsType);

	TArray<class UEquipment*>& GetEquipments()
	{
		return EquipmentArray;
	}

	class UWeapon* CreateWeapon(int index);

public:
	UPROPERTY(VisibleAnywhere)
	FOnEquipmentUpdated OnEquipmentUpdated;

	UPROPERTY(VisibleAnywhere)
	FOnWeaponUpdated OnWeaponUpdated;

public:
	TArray<UEquipment*> EquipmentArray;

	UPROPERTY(VisibleAnywhere)
	TArray<USkeletalMeshComponent*> SkeletalMeshArray;
	UPROPERTY(VisibleAnywhere)
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
