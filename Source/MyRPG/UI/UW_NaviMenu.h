#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NaviMenu.generated.h"

// (네비게이션 메뉴 선택 UI)
UCLASS()
class MYRPG_API UUW_NaviMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	void ShowUpAnim();

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* CreateServerBtn;
	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinServerBtn;
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ShowUp;

private:
	UFUNCTION()
	void CreateServerHandler();
	UFUNCTION()
	void JoinServerHandler();
};
