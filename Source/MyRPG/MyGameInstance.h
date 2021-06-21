#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class MYRPG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	struct FItemData* GetItemData(int32 Index);
	struct FEquipmentData* GetEquipmentData(int32 Index);
	struct FWeaponData* GetWeaponData(int32 Index);
	
public:
	void SetUserName(FString NewUserName);
	FString GetUserName();

private:
	FString UserName;

	UPROPERTY()
	class UDataTable* ItemDataTable;
	UPROPERTY()
	class UDataTable* EquipmentDataTable;
	UPROPERTY()
	class UDataTable* WeaponDataTable;
};
