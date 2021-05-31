#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class MYRPG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void SetUserName(FString NewUserName);
	FString GetUserName();

private:
	FString UserName;
};
