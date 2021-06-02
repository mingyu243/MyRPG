#include "Main_HUD.h"

#include "../UI/UW_Main.h"

AMain_HUD::AMain_HUD()
{
	static ConstructorHelpers::FClassFinder<UUW_Main> WB_Main(TEXT("WidgetBlueprint'/Game/Blueprints/UI/WB/Main/WB_Main.WB_Main_C'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void AMain_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject();
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	if (!CheckUIObject()) return;

	MainUIObject->AddChatMessage(Message);
}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

bool AMain_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr)
	{
		return CreateUIObject();
	}
	return true;
}

bool AMain_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UUW_Main>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true;
		}
	}
	return false;
}
