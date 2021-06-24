#include "InventoryComponent.h"

#include "../Item/Item.h"
#include "../Item/Weapon.h"

UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UItem* Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UInventoryComponent::AddItem(class UItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(class UItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);

		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}
