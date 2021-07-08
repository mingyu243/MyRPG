#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Unit.h"
#include "../../Component/EquipmentComponent.h"
#include "Player_Base.generated.h"

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	NO_WEAPON,
	SWORD_SHIELD,
	TWO_HAND_SWORD,
	DOUBLE_SWORD,
	BOW,
	MAGIC_WAND
};

UCLASS()
class MYRPG_API APlayer_Base : public AUnit
{
	GENERATED_BODY()

public:
	APlayer_Base();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

public:
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; };
	class UInventoryComponent* GetInventoryComponent() { return Inventory; };

	void Attack();
	UFUNCTION(Server, UnReliable)
	void CtoS_Attack();
	UFUNCTION(NetMulticast, UnReliable)
	void MC_Attack();

	UFUNCTION()
	bool UseItem(class UItem* Item);
	UFUNCTION()
	bool TakeOffEquipment(class UEquipment* Equipment, EAllMeshPartsType PartsType);

public:
	UPROPERTY(VisibleAnywhere)
	ECombatType CurrentCombatType;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class UEquipmentComponent* EquipmentComponent;
	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* Inventory;
	UPROPERTY(VisibleAnywhere)
	class USceneCaptureComponent2D* SceneCapture;

private:
	UPROPERTY(VisibleAnywhere)
	class UPlayerAnim* AnimBP;

	UPROPERTY(VisibleAnywhere)
	bool IsAttacking;
	UPROPERTY(VisibleAnywhere)
	bool IsComboInputOn;
	UPROPERTY(VisibleAnywhere)
	bool CanNextCombo;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentCombo;
	UPROPERTY(VisibleAnywhere)
	int32 MaxCombo;
	
private:
	UFUNCTION()
	void LookUp(float AxisValue);
	UFUNCTION()
	void Turn(float AxisValue);
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void StartJump();

	// 무기에 따른 전투 방식 결정.
	UFUNCTION()
	void CheckCombatType(class UEquipment* WeaponL, class UEquipment* WeaponR);

private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void NextAttackCheck();

	void AttackStartComboState();
	void AttackEndComboState();
};