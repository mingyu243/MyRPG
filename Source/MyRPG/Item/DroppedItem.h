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
	void SetItem(int32 index);

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PreviewMesh;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentItemIndex;

private:
	void SetPreviewMesh(class UStaticMesh* Mesh);
};
