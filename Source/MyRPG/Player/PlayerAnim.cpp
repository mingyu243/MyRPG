#include "PlayerAnim.h"

#include "Player_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
	bIsInAir = false;
	bCanAttack = true;
	CurrentComboIndex = 0;
	MaxComboIndex = 3;
}

void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Player = Cast<APlayer_Base>(Pawn);
	}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player == nullptr || Player->IsValidLowLevel() == false)
	{
		return;
	}

	Speed = Player->GetVelocity().Size();
	Direction = CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());

	bIsInAir = Player->GetCharacterMovement()->IsFalling();
}

void UPlayerAnim::Attack()
{
	if (bCanAttack == false)
	{
		UE_LOG(LogClass, Warning, TEXT("Cant Next Attack"));
		return;
	}
	bCanAttack = false;

	CurrentComboIndex %= MaxComboIndex;
	CurrentComboIndex++;

	UE_LOG(LogClass, Warning, TEXT("Attack(%d)"), CurrentComboIndex);
	bIsAttack = true;
}