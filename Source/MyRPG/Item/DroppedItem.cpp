#include "DroppedItem.h"

ADroppedItem::ADroppedItem()
{
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PREVIEWMESH"));
	RootComponent = PreviewMesh;
}

void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADroppedItem::SetItem(int32 index)
{
	// 게임인스턴스에서 받아옴.
}
