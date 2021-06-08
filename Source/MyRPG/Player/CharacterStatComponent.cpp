#include "CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
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
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
	}
}

float UCharacterStatComponent::GetDamage()
{
	return Attack;
}
