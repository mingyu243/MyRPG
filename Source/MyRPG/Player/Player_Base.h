#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Base.generated.h"

UCLASS()
class MYRPG_API APlayer_Base : public ACharacter
{
	GENERATED_BODY()

public:
	APlayer_Base();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

public:
	void SetWeapon(class AWeapon* NewWeapon);
	void Attack();

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class AWeapon* CurrentWeapon;

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

private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void NextAttackCheck();
	void AttackHitCheck();

	void AttackStartComboState();
	void AttackEndComboState();
};