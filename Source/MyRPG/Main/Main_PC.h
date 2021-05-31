#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Main_PC.generated.h"

UCLASS()
class MYRPG_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	void SendMessage(const FText& Text);

private:
	UFUNCTION(Server, Unreliable)
	void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
	void StoC_SendMessage(const FString& Message);
};
