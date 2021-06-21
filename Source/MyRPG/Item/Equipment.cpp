#include "Equipment.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UEquipment::Init(int32 index)
{
	Super::Init(index);

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		CurrentEquipmentData = GI->GetEquipmentData(index);
	}
}

void UEquipment::Use(APlayer_Base* Character)
{
	Super::Use(Character);
}

FEquipmentData* UEquipment::GetEquipmentData()
{
	return CurrentEquipmentData;
}