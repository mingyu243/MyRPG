#include "Main_HUD.h"

#include "../UI/UW_Main.h"
#include "../UI/UW_Inventory.h"

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
	
	CreateUIObject();
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	if (CreateUIObject() == false) return;

	MainUIObject->AddChatMessage(Message);
}

void AMain_HUD::ToggleInventory(bool isShow)
{
	if (CreateUIObject() == false) return;

	MainUIObject->ShowInventory(isShow);
	MainUIObject->ShowEquipment(isShow);
}

void AMain_HUD::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	if (CreateUIObject() == false) return;

	MainUIObject->BindCharacterStat(CharacterStat);
}

void AMain_HUD::BindInventory(class UInventoryComponent* Inventory)
{
	if (CreateUIObject() == false) return;

	MainUIObject->BindInventory(Inventory);
}

void AMain_HUD::BindEquipment(class UEquipmentComponent* Equipment)
{
	if (CreateUIObject() == false) return;

	MainUIObject->BindEquipment(Equipment);
}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

bool AMain_HUD::CreateUIObject()
{
	if (MainUIObject)
	{
		return true;
	}

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
