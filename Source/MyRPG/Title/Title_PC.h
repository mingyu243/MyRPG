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

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUW_Title> TitleUIClass;
	class UUW_Title* TitleUIObject;

	virtual void BeginPlay() override;

	void CreateServer();
	void JoinServer(FString IPAddress);
};
