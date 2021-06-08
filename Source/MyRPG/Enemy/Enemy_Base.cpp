#include "Enemy_Base.h"

#include "../Player/CharacterStatComponent.h"

#include "Perception/PawnSensingComponent.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PAWNSENSING"));
	CharacterStat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CHARACTERSTAT"));

}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
