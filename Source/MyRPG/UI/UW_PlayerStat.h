#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_PlayerStat.generated.h"

UCLASS()
class MYRPG_API UUW_PlayerStat : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);

private:
	TWeakObjectPtr<class UCharacterStatComponent> CurrentCharacterStat;
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* PlayerName;
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* HPText;

private:
	void UpdateCharacterStat();
};
