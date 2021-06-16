#include "UW_PlayerStat.h"

#include "../Component/CharacterStatComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUW_PlayerStat::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	if (CharacterStat == nullptr) return;
	CurrentCharacterStat = CharacterStat;
	UpdateCharacterStat();

	CharacterStat->OnHPChanged.AddUObject(this, &UUW_PlayerStat::UpdateCharacterStat);
}

void UUW_PlayerStat::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid() == false) return;

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"), CurrentCharacterStat->GetCurrentHP(), CurrentCharacterStat->GetMaxHP())));
}
