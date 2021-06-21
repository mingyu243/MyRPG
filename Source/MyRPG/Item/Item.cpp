#include "Item.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UItem::Init(int32 index)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		CurrentItemData = GI->GetItemData(index);
	}
}

FItemData* UItem::GetItemData()
{
	return CurrentItemData;
}

void UItem::Use(APlayer_Base* Character)
{
}
