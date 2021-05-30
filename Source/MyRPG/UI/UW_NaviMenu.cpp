#include "UW_NaviMenu.h"

#include "../Title/Title_PC.h"

#include "Components/Button.h"

void UUW_NaviMenu::NativeConstruct()
{
	Super::NativeConstruct();

	CreateServerBtn->OnClicked.AddDynamic(this, &UUW_NaviMenu::CreateServerHandler);
	JoinServerBtn->OnClicked.AddDynamic(this, &UUW_NaviMenu::JoinServerHandler);
}

void UUW_NaviMenu::CreateServerHandler()
{
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->CreateServer();
	}
}

void UUW_NaviMenu::JoinServerHandler()
{
	ATitle_PC* MyPC = Cast<ATitle_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->JoinServer(TEXT("127.0.0.1"));
	}
}
