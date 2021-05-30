#include "Title_PC.h"

#include "../UI/UW_Title.h"

#include "Kismet/GameplayStatics.h"

ATitle_PC::ATitle_PC()
{
	static ConstructorHelpers::FClassFinder<UUW_Title> WB_Title(TEXT("WidgetBlueprint'/Game/Blueprints/UI/WB/WB_Title.WB_Title_C'"));
	if (WB_Title.Succeeded())
	{
		TitleUIClass = WB_Title.Class;
	}
}

void ATitle_PC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		TitleUIObject = CreateWidget<UUW_Title>(this, TitleUIClass);
		TitleUIObject->AddToViewport();

		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());

		TitleUIObject
	}
}

void ATitle_PC::CreateServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Main"), true, ((FString)(L"Listen")));
}

void ATitle_PC::JoinServer(FString IPAddress)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(IPAddress));
}
