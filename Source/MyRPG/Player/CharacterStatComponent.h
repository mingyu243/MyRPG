#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYRPG_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	UPROPERTY(VisibleAnywhere)
	float MaxHP;
	UPROPERTY(VisibleAnywhere)
	float CurrentHP;

	// 각종 스탯들.

		
};
