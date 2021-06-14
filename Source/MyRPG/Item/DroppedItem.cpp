#include "DroppedItem.h"

#include "../MyGameInstance.h"
#include "../CustomDataTables.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"

ADroppedItem::ADroppedItem()
{
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PREVIEWMESH"));
	RootComponent = PreviewMesh;
}

void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();

	SetItem(100);
}

void ADroppedItem::SetItem(int32 index)
{
	CurrentItemIndex = index;

	// 게임인스턴스에서 받아옴.
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(NULL, *(GI->GetItemData(CurrentItemIndex)->Path_Mesh));
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
