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
	FWeaponData() : Enum_WeaponType(EWeaponType::SWORD), Path_AM_BasicAttackCombo(TEXT("")){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponType Enum_WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Path_AM_BasicAttackCombo;
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	// Armor
	FACE,
	HAIR,
	GLOVE,
	SHOE,
	HEADGEARS,
	SHOULDERPAD,
	BELT,

	// Weapon
	WEAPON
};

USTRUCT(BlueprintType)
struct FEquipmentData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEquipmentData() : Index(100), Enum_EquipmentType(EEquipmentType::FACE), Stat_Defense(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EEquipmentType Enum_EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Stat_Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Stat_HP;
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	POTION,
	EQUIPMENT
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData() : Index(100), ItemName(TEXT("DefaultName")), Description(TEXT("DefaultDescription")), Enum_ItemType(EItemType::EQUIPMENT), Path_Icon(TEXT("")), Path_Mesh(TEXT("")) {}
	
	// 데이터 테이블에서의 키 값은 더미 값으로 만들었다.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName ItemName;
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
