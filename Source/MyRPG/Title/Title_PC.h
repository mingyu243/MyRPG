#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Title_PC.generated.h"

UCLASS()
class MYRPG_API ATitle_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATitle_PC();
	virtual void BeginPlay() override;

public:
	void CreateServer();
	void JoinServer(const FString& IPAddress);

private:
	TSubclassOf<class UUW_Title> TitleUIClass;
	class UUW_Title* TitleUIObject;
};
