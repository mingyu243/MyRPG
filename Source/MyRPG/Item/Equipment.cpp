#include "Equipment.h"

#include "../MyGameInstance.h"
#include "../Unit/Player/Player_Base.h"
#include "../Component/EquipmentComponent.h"
#include "../Component/InventoryComponent.h"

#include "Kismet/GameplayStatics.h"

void UEquipment::Init(int32 index, UWorld* CurrentWorld)
{
	Super::Init(index, CurrentWorld);

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (GI)
	{
		CurrentEquipmentData = GI->GetEquipmentData(index);
	}
}

void UEquipment::Use(APlayer_Base* Character)
{
	Super::Use(Character);

	UEquipment* ReturnEquipment = Character->GetEquipmentComponent()->SetEquipment(this);
	if (ReturnEquipment)
	{
		Character->GetInventoryComponent()->AddItem(ReturnEquipment);
	}
}

FEquipmentData* UEquipment::GetEquipmentData()
{
	return CurrentEquipmentData;
}