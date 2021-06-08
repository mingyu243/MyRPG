#include "Enemy_Base.h"

#include "Enemy_AC.h"

#include "Perception/PawnSensingComponent.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PAWNSENSING"));

	AIControllerClass = AEnemy_AC::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
