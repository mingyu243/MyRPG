#include "CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	Attack = 10;
	MaxHP = 100;
	CurrentHP = MaxHP;
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

float UCharacterStatComponent::GetMaxHP()
{
	return MaxHP;
}

float UCharacterStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

float UCharacterStatComponent::GetHPRatio()
{
	return (CurrentHP / MaxHP);
}

float UCharacterStatComponent::GetAttack()
{
	return Attack; // 나중에 장비에 의한 공격력 계산도 할 듯 ?
}

float UCharacterStatComponent::GetFinalDamage(float DamageStatic, float DamageMul)
{
	return DamageStatic + (GetAttack() * DamageMul); 
}
