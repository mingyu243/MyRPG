#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttackHitCheck.generated.h"

UCLASS()
class MYRPG_API UAnimNotify_AttackHitCheck : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Offset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageStatic;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageMul = 1.0f;
};
