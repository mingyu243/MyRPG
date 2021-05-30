#include "PlayerAnim.h"

#include "Player_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
	bIsInAir = false;
}

void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Character = Cast<ACharacter>(Pawn);
	}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
	{
		return;
	}

	Speed = Character->GetVelocity().Size();
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());

	bIsInAir = Character->GetCharacterMovement()->IsFalling();
}
