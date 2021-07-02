#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentUpdated);

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

public:
	UPROPERTY(VisibleAnywhere)
	FOnEquipmentUpdated OnEquipmentUpdated;

	//class AWeapon* GetWeapon();
	//void SetWeapon(class AWeapon* NewWeapon);

public:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* HeadGears;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Hair;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Face;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* ShoulderPad;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* BodyMesh;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Backpack;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Belt;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Glove;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Shoe;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Shield;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RightWeapon;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LeftWeapon;

	//UPROPERTY(VisibleAnywhere)
	//class AWeapon* CurrentWeapon;
};
