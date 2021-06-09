#include "Unit.h"

#include "../Component/CharacterStatComponent.h"

AUnit::AUnit()
{
	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CHARACTERSTAT"));
}

UCharacterStatComponent* AUnit::GetCharacterStat()
{
	return CharacterStat;
}