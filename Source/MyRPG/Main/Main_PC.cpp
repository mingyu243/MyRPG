#include "Main_PC.h"

#include "../MyGameInstance.h"
#include "Main_HUD.h"

#include "Kismet/GameplayStatics.h"

AMain_PC::AMain_PC()
{
	bIsShowingInventory = false;
}

void AMain_PC::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void AMain_PC::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMain_PC::FocusChatInputText);
	InputComponent->BindAction(TEXT("ToggleInventory"), EInputEvent::IE_Pressed, this, &AMain_PC::ToggleInventory);
}

void AMain_PC::SendMessage(const FText& Text)
{
	UMyGameInstance* MyGI = GetGameInstance<UMyGameInstance>();
	if (MyGI)
	{
		FString UserName = MyGI->GetUserName();
		FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

		CtoS_SendMessage(Message);
	}
}

void AMain_PC::FocusChatInputText()
{
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}

void AMain_PC::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}

void AMain_PC::FocusGameAndUI()
{
	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);
}

void AMain_PC::FocusUI()
{
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void AMain_PC::CtoS_SendMessage_Implementation(const FString& Message)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMain_PC* PC = Cast<AMain_PC>(OutActor);
		if (PC)
		{
			PC->StoC_SendMessage(Message);
		}
	}
}

void AMain_PC::StoC_SendMessage_Implementation(const FString& Message)
{
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}

void AMain_PC::ToggleInventory()
{
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	bIsShowingInventory = !bIsShowingInventory;
	bIsShowingInventory ? FocusGameAndUI() : FocusGame();

	HUD->ToggleInventory(bIsShowingInventory);
}
