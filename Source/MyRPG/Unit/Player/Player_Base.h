#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Unit.h"
#include "Player_Base.generated.h"

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
	class UEquipmentComponent* GetEquipmentComponent();

	void Attack();
	UFUNCTION(Server, UnReliable)
	void CtoS_Attack();
	UFUNCTION(NetMulticast, UnReliable)
	void MC_Attack();

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class UEquipmentComponent* Equipment;

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

private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void NextAttackCheck();

	void AttackStartComboState();
	void AttackEndComboState();
};