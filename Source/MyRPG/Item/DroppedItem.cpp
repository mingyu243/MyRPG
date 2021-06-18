#include "DroppedItem.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"
#include "Item.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

ADroppedItem::ADroppedItem()
{
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PREVIEWMESH"));
	RootComponent = PreviewMesh;
}

void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();
}

void ADroppedItem::SetItem(AItem* Item)
{
	if (Item == nullptr) return;

	CurrentItem = Item;
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(NULL, *(GI->GetItemData(Item->GetItemData()->Index)->Path_Mesh));
		if (LoadedMesh)
		{
			SetPreviewMesh(LoadedMesh);
		}
	}
}

void ADroppedItem::SetPreviewMesh(UStaticMesh* Mesh)
{
	PreviewMesh->SetStaticMesh(Mesh);
}
