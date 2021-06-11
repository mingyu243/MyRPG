#include "MyGameInstance.h"

#include "CustomDataTables.h"

#include "Kismet/KismetMathLibrary.h"

UMyGameInstance::UMyGameInstance()
{
	FString ItemDataPath = TEXT("DataTable'/Game/Blueprints/DataTable/ItemDataTable.ItemDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Item(*ItemDataPath);
	if (DT_Item.Succeeded())
	{
		ItemDataTable = DT_Item.Object;
	}
}

FItemData* UMyGameInstance::GetItemData(int32 Index)
{
	return ItemDataTable->FindRow<FItemData>(*FString::FromInt(Index), TEXT(""));
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
