#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroppedItem.generated.h"

UCLASS()
class MYRPG_API ADroppedItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ADroppedItem();
	virtual void BeginPlay() override;

public:
	void SetItem(class AItem* Item);

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PreviewMesh;

private:
	class AItem* CurrentItem;

private:
	void SetPreviewMesh(class UStaticMesh* Mesh);
};
