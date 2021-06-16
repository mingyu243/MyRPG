#include "PlayerAnim.h"

#include "Player_Base.h"
#include "../../Item/Weapon.h"
#include "../../CustomDataTables.h"
#include "../../Component/EquipmentComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnim::UPlayerAnim()
{
	bIsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack_SwordShield(TEXT("AnimMontage'/Game/Blueprints/Player/Animation/Sword_Shield/Combo_SwordShield.Combo_SwordShield'"));
	if (AM_Attack_SwordShield.Succeeded())
	{
		AM_SwordShield = AM_Attack_SwordShield.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack_DoubleSword(TEXT("AnimMontage'/Game/Blueprints/Player/Animation/Double_Sword/Combo_DoubleSword.Combo_DoubleSword'"));
	if (AM_Attack_DoubleSword.Succeeded())
	{
		AM_DoubleSword = AM_Attack_DoubleSword.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack_TwoHandSword(TEXT("AnimMontage'/Game/Blueprints/Player/Animation/TwoHand_Sword/Combo_TwoHand.Combo_TwoHand'"));
	if (AM_Attack_TwoHandSword.Succeeded())
	{
		AM_TwoHandSword = AM_Attack_TwoHandSword.Object;
	}
	CurrentCombatType = ECombatType::TWO_HAND_SWORD;
	CheckCombatType();
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
	// CurrentCombatType = Player->GetEquipmentComponent()->GetWeapon()->GetWeaponData()->Enum_WeaponType;
}

void UPlayerAnim::PlayAttackMontage()
{
	if (IsDead) return;

	Montage_Play(CurrentAttackMontage, 1.0f);
}

void UPlayerAnim::JumpToAttackMontageSection(int32 NewSection)
{
	if (IsDead) return;

	if (Montage_IsPlaying(CurrentAttackMontage))
	{
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), CurrentAttackMontage);
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

void UPlayerAnim::CheckCombatType()
{
	// 나중에 무기 교체할 때마다 체크할 예정.

	switch (CurrentCombatType)
	{
	case ECombatType::SWORD_SHIELD:
		CurrentAttackMontage = AM_SwordShield;
		break;
	case ECombatType::DOUBLE_SWORD:
		CurrentAttackMontage = AM_DoubleSword;
		break;
	case ECombatType::TWO_HAND_SWORD:
		CurrentAttackMontage = AM_TwoHandSword;
		break;
	}
}
