#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Unit.h"
#include "Enemy_Base.generated.h"

UCLASS()
class MYRPG_API AEnemy_Base : public AUnit
{
	GENERATED_BODY()

public:
	AEnemy_Base();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensing;
};
