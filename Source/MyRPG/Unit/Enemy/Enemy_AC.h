#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AC.generated.h"

UCLASS()
class MYRPG_API AEnemy_AC : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_AC();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName Key_HomePos;
	static const FName Key_PatrolPos;
	static const FName Key_Target;

	void RunAI();
	void StopAI();
	
private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
