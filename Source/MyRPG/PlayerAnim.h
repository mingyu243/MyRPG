// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYRPG_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction;
};