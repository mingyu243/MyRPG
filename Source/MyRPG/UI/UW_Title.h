#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Title.generated.h"

// (Title Level의 메인 UI)
UCLASS()
class MYRPG_API UUW_Title : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
public:
	void StartAnim();
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UUW_NaviMenu* WB_NaviMenu;
};
