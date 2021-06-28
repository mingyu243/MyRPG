#include "MyGameInstance.h"

#include "CustomDataTables.h"

#include "Kismet/KismetMathLibrary.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Item(TEXT("DataTable'/Game/Blueprints/DataTable/ItemDataTable.ItemDataTable'"));
	if (DT_Item.Succeeded())
	{
		ItemDataTable = DT_Item.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Equipment(TEXT("DataTable'/Game/Blueprints/DataTable/EquipmentDataTable.EquipmentDataTable'"));
	if (DT_Equipment.Succeeded())
	{
		EquipmentDataTable = DT_Equipment.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Weapon(TEXT("DataTable'/Game/Blueprints/DataTable/WeaponDataTable.WeaponDataTable'"));
	if (DT_Weapon.Succeeded())
	{
		WeaponDataTable = DT_Weapon.Object;
	}
}

FItemData* UMyGameInstance::GetItemData(int32 Index)
{
	return ItemDataTable->FindRow<FItemData>(*FString::FromInt(Index), TEXT(""));
}

FEquipmentData* UMyGameInstance::GetEquipmentData(int32 Index)
{
	return EquipmentDataTable->FindRow<FEquipmentData>(*FString::FromInt(Index), TEXT(""));
}

FWeaponData* UMyGameInstance::GetWeaponData(int32 Index)
{
	return WeaponDataTable->FindRow<FWeaponData>(*FString::FromInt(Index), TEXT(""));
}

void UMyGameInstance::SetUserName(FString NewUserName)
{
	UserName = NewUserName;
}

FString UMyGameInstance::GetUserName()
{
	if (UserName.IsEmpty())
	{
		int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 9999);
		UserName = FString::Printf(TEXT("Guest_%d"), RandomNumber);
	}

	return UserName;
}
