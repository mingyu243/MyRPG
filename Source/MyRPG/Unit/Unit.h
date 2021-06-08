#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"

UCLASS()
class MYRPG_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	AUnit();

public:
	class UCharacterStatComponent* GetCharacterStat();

private:	
	UPROPERTY(VisibleAnywhere)
	class UCharacterStatComponent* CharacterStat;
};
