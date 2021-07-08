#include "Item.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UItem::Init(int32 index, UWorld* CurrentWorld)
{
	CurrnetIndex = index;
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (GI)
	{
		CurrentItemData = GI->GetItemData(CurrnetIndex);
	}
}

void UItem::Use(APlayer_Base* Character)
{
	UE_LOG(LogClass, Warning, TEXT("Item Use"));
}

FItemData* UItem::GetItemData()
{
	return CurrentItemData;
}