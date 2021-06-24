#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Templates/SharedPointer.h"
#include "Main_PC.generated.h"

UCLASS()
class MYRPG_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMain_PC();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
public:
	void SendMessage(const FText& Text);

public:
	UFUNCTION()
	void FocusChatInputText();
	UFUNCTION()
	void FocusGame();
	UFUNCTION()
	void FocusGameAndUI();
	UFUNCTION()
	void FocusUI();

private:
	UFUNCTION(Server, Unreliable)
	void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
	void StoC_SendMessage(const FString& Message);

	bool bIsShowingInventory;

private:
	void ToggleInventory();
};
