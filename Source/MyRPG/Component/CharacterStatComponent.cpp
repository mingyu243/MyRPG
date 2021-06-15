#include "CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	Attack = 10;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UCharacterStatComponent::Attacked(float Damage)
{
	float NewHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);
	SetHP(NewHP);
}

void UCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
	}
}

float UCharacterStatComponent::GetHPRatio()
{
	return (CurrentHP / MaxHP);
}

float UCharacterStatComponent::GetDamage()
{
	return Attack;
}