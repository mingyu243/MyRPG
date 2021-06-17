#include "AnimNotify_AttackHitCheck.h"

#include "../Unit/Unit.h"
#include "../Component/CharacterStatComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	FVector Pos = MeshComp->GetComponentLocation()
		+ MeshComp->GetRightVector() * Offset.X
		+ MeshComp->GetForwardVector() * Offset.Y
		+ MeshComp->GetUpVector() * Offset.Z;

	UKismetSystemLibrary::DrawDebugSphere(MeshComp->GetWorld(), Pos, Radius, 12, FLinearColor::White, 2.0f, 0.0f);

	AUnit* MyUnit = Cast<AUnit>(MeshComp->GetOwner());
	if (MyUnit == nullptr) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	TArray<AActor*> OutActors;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreActors.Add(MyUnit);
	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(MeshComp->GetWorld(), Pos, Radius, ObjectTypes, nullptr, IgnoreActors, OutActors);
	if (IsOverlapped)
	{
		for (AActor* OutActor : OutActors)
		{
			float DamagePower = MyUnit->GetCharacterStat()->GetFinalDamage(DamageStatic, DamageMul);
			UE_LOG(LogClass, Warning, TEXT("ApplyDamage : %f"), DamagePower);
			UGameplayStatics::ApplyDamage(OutActor, DamagePower, MyUnit->GetController(), nullptr, NULL);
		}
	}
}

FString UAnimNotify_AttackHitCheck::GetNotifyName_Implementation() const
{
	return FString(TEXT("AttackHitCheck"));
}
