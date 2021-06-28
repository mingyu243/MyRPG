#include "Equipment.h"

#include "../MyGameInstance.h"

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
}

FEquipmentData* UEquipment::GetEquipmentData()
{
	return CurrentEquipmentData;
}