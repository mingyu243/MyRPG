#include "PlayerAnim.h"

#include "Player_Base.h"
#include "../../Item/Weapon.h"

#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
	bIsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack(TEXT("AnimMontage'/Game/Blueprints/Player/Animation/Combo_SwordShield.Combo_SwordShield'"));
	if (AM_Attack.Succeeded())
	{
		AttackMontage = AM_Attack.Object;
	}
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
	CurrentWeaponType = Player->GetWeapon()->GetWeaponType();
}

void UPlayerAnim::PlayAttackMontage()
{
	if (IsDead) return;

	Montage_Play(AttackMontage, 1.0f);
}

void UPlayerAnim::JumpToAttackMontageSection(int32 NewSection)
{
	if (IsDead) return;

	if (Montage_IsPlaying(AttackMontage))
	{
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	}
}

void UPlayerAnim::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UPlayerAnim::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
