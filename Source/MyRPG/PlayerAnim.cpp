// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	Speed = Pawn->GetVelocity().Size();
	Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
}
