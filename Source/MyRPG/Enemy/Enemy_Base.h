#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_Base.generated.h"

UCLASS()
class MYRPG_API AEnemy_Base : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy_Base();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleAnywhere)
	class UCharacterStatComponent* CharacterStat;

};
