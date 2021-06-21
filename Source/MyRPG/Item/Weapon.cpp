#include "Weapon.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UWeapon::Init(int32 index)
{
	Super::Init(index);

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		CurrentWeaponData = GI->GetWeaponData(index);
	}
}

void UWeapon::Use(APlayer_Base* Character)
{
	Super::Use(Character);
}

FWeaponData* UWeapon::GetWeaponData()
{
	return CurrentWeaponData;
}
