#include "Enemy_Base.h"

#include "Perception/PawnSensingComponent.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PAWNSENSING"));

}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
