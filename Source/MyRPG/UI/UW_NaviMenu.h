#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NaviMenu.generated.h"

UCLASS()
class MYRPG_API UUW_NaviMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* CreateServerBtn;
	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinServerBtn;

	UPROPERTY(Meta = (BindWidgetAnim))
	class UWidgetAnimation* ShowUp;

	UFUNCTION()
	void CreateServerHandler();
	UFUNCTION()
	void JoinServerHandler();
};
