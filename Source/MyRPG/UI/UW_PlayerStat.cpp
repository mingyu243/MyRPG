#include "UW_PlayerStat.h"

#include "../Component/CharacterStatComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUW_PlayerStat::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	if (nullptr == CharacterStat) return;
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UUW_PlayerStat::UpdateCharacterStat);
}

void UUW_PlayerStat::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid() == false) return;

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}
