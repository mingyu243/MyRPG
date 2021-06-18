#include "Equipment.h"

void AEquipment::Init(int32 index)
{
	Super::Init(index);
}

void AEquipment::Use()
{
	Super::Use();
}

FEquipmentData* AEquipment::GetEquipmentData()
{
	return CurrentEquipmentData;
}