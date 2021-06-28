#include "Item.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UItem::Init(int32 index, UWorld* CurrentWorld)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (GI)
	{
		CurrentItemData = GI->GetItemData(index);
	}
}

void UItem::Use(APlayer_Base* Character)
{
	UE_LOG(LogClass, Warning, TEXT("Use"));
}

FItemData* UItem::GetItemData()
{
	return CurrentItemData;
}