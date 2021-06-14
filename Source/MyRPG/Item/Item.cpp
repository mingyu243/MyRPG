#include "Item.h"

#include "../CustomDataTables.h"

AItem::AItem()
{

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	

}

void AItem::Use()
{
	UE_LOG(LogClass, Warning, TEXT("Item Use"));
}

FItemData* AItem::GetItemData()
{
	return CurrentItemData;
}