#include "Unit.h"

#include "CharacterStatComponent.h"

AUnit::AUnit()
{
	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
}

UCharacterStatComponent* AUnit::GetCharacterStat()
{
	return CharacterStat;
}