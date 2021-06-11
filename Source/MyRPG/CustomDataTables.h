#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Item/Item.h"
#include "CustomDataTables.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData() : Name(TEXT("DefaultName")), Description(TEXT("DefaultDescription")), Path_Icon(TEXT("")), Path_Mesh(TEXT("")) {}
	
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
