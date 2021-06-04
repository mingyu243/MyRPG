#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

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
	FOnAttackHitCheckDelegate OnAttackHitCheck;

public:
	void SetDeadAnim() { IsDead = true; }
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

private:
	UPROPERTY(VisibleAnywhere)
	class APlayer_Base* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool IsDead;
	
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AttackMontage;

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	UFUNCTION()
	void AnimNotify_NextAttackCheck();
	
	FName GetAttackMontageSectionName(int32 Section);
};
