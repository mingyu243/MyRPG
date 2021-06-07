#include "UW_Title.h"

#include "UW_NaviMenu.h"

void UUW_Title::NativeConstruct()
{
	WB_NaviMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UUW_Title::StartAnim()
{
	WB_NaviMenu->ShowUpAnim();
}