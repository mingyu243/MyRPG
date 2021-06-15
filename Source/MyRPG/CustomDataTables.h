#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomDataTables.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	SWORD,
	SHIELD,
	BOW,
	MAGIC_WAND
};

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWeaponData() : Enum_WeaponType(EWeaponType::SWORD), Path_AM_BasicAttack(TEXT("")), Range(0) {}

	// 데이터 테이블에서의 키 값.
	// int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponType Enum_WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Path_AM_BasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Range;
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	POTION,
	ARMOR,
	WEAPON
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData() : Name(TEXT("DefaultName")), Description(TEXT("DefaultDescription")), Enum_ItemType(EItemType::ARMOR), Path_Icon(TEXT("")), Path_Mesh(TEXT("")) {}
	
	// 데이터 테이블에서의 키 값.
	// int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemType Enum_ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Path_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Path_Mesh;
};

UCLASS()
class MYRPG_API UCustomDataTables : public UDataTable
{
	GENERATED_BODY()
	
};
