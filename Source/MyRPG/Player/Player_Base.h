#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Base.generated.h"

UCLASS()
class MYRPG_API APlayer_Base : public ACharacter
{
	GENERATED_BODY()

public:
	APlayer_Base();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

private:
	UFUNCTION()
	void LookUp(float AxisValue);
	UFUNCTION()
	void Turn(float AxisValue);
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void FocusChatInputText();
};