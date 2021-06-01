#include "Title_PC.h"

#include "../UI/UW_Title.h"

#include "Kismet/GameplayStatics.h"

ATitle_PC::ATitle_PC()
{
	static ConstructorHelpers::FClassFinder<UUW_Title> WB_Title(TEXT("WidgetBlueprint'/Game/Blueprints/UI/WB/Title/WB_Title.WB_Title_C'"));
	
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
		//TitleUIObject->SetVisibility(ESlateVisibility::Hidden);

		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());

		FTimerHandle StartAnimDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(StartAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				//TitleUIObject->SetVisibility(ESlateVisibility::Visible);
				TitleUIObject->StartAnim();
			}), 1.0f , false);
	}
}

void ATitle_PC::CreateServer()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Main"), true, ((FString)(L"Listen")));
}

void ATitle_PC::JoinServer(const FString& IPAddress)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(IPAddress));
}
