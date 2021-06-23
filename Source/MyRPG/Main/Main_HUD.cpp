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

	static ConstructorHelpers::FClassFinder<UUW_Inventory> WB_Inventory(TEXT("WidgetBlueprint'/Game/Blueprints/UI/WB/WB_Inventory.WB_Inventory_C'"));
	if (WB_Inventory.Succeeded())
	{
		InventoryUIClass = WB_Inventory.Class;
	}
}

void AMain_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (CreateUIObject(MainUIClass, &MainUIObject))
	{
		UE_LOG(LogClass, Warning, TEXT("createUI"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("Error"));
	}

	CreateUIObject(InventoryUIClass, &InventoryUIObject);
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	if (CreateUIObject(MainUIClass, &MainUIObject) == false) return;

	MainUIObject->AddChatMessage(Message);
}

void AMain_HUD::ToggleInventory(bool isShow)
{
	if (CreateUIObject(InventoryUIClass, &InventoryUIObject) == false) return;

	//InventoryUIObject->ShowInventory(!(InventoryUIObject->isShowInventory()));
}

void AMain_HUD::BindCharacterStat(UCharacterStatComponent* CharacterStat)
{
	if (CreateUIObject(MainUIClass, &MainUIObject) == false) return;

	MainUIObject->BindCharacterStat(CharacterStat);
}

void AMain_HUD::BindInventory(class UInventoryComponent* Inventory)
{
	if (CreateUIObject(InventoryUIClass, &InventoryUIObject) == false) return;


}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

template <typename T_UMGClass>
bool AMain_HUD::CreateUIObject(TSubclassOf<T_UMGClass> UIClass, T_UMGClass** UIObject)
{
	if ((*UIObject) == nullptr && UIClass)
	{
		(*UIObject) = CreateWidget<T_UMGClass>(GetOwningPlayerController(), UIClass);
		if ((*UIObject))
		{
			(*UIObject)->AddToViewport();
			return true;
		}
	}
	return false;
}
