#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class MYRPG_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnim();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayer_Base* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxComboIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentComboIndex;

public:
	void Attack();
};
