#include "Item.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Engine/Engine.h"

void AItem::Init(int32 index)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		CurrentItemData = GI->GetItemData(index);
	}
}

void AItem::Use()
{
	UE_LOG(LogClass, Warning, TEXT("Item Use"));
}

FItemData* AItem::GetItemData()
{
	return CurrentItemData;
}