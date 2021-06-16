#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Main_HUD.generated.h"

UCLASS()
class MYRPG_API AMain_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMain_HUD();
	virtual void BeginPlay() override;

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);

	void BindCharacterStat(class UCharacterStatComponent* CharacterStat);

private:
	TSubclassOf<class UUW_Main> MainUIClass;
	class UUW_Main* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
