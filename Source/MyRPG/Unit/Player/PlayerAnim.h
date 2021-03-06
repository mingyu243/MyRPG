#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player_Base.h"
#include "PlayerAnim.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);

UCLASS()
class MYRPG_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnim();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;

public:
	void SetDeadAnim() { IsDead = true; }
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

	UFUNCTION()
	void SetCombatType(ECombatType Type);

private:
	UPROPERTY(VisibleAnywhere)
	APlayer_Base* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool IsDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	ECombatType CurrentCombatType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* CurrentAttackMontage;
	
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AM_SwordShield;
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AM_DoubleSword;
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AM_TwoHandSword;

private:
	UFUNCTION()
	void AnimNotify_NextAttackCheck();
	
	FName GetAttackMontageSectionName(int32 Section);

	UFUNCTION()
	void UpdateCombatType();
};
