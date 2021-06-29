#include "Weapon.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Kismet/GameplayStatics.h"

void UWeapon::Init(int32 index, UWorld* CurrentWorld)
{
	Super::Init(index, CurrentWorld);

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (GI)
	{
		CurrentWeaponData = GI->GetWeaponData(index);
	}
}

void UWeapon::Use(APlayer_Base* Character)
{
	Super::Use(Character);

	UE_LOG(LogClass, Warning, TEXT("Weapon Use"));
}

FWeaponData* UWeapon::GetWeaponData()
{
	return CurrentWeaponData;
}
