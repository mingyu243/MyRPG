#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPG_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void Attacked(float Damage);
	void SetHP(float NewHP);
	float GetMaxHP();
	float GetCurrentHP();
	float GetHPRatio();
	float GetDamage();

	FOnHPChangedDelegate OnHPChanged;

private:
	UPROPERTY(VisibleAnywhere)
	float MaxHP;
	UPROPERTY(VisibleAnywhere)
	float CurrentHP;
	
	UPROPERTY(VisibleAnywhere)
	float Attack;
	
	// 각종 직업 별 스탯.
		
};
