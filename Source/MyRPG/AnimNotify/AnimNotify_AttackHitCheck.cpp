#include "AnimNotify_AttackHitCheck.h"

#include "../Player/Player_Base.h"
#include "../Player/CharacterStatComponent.h"

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

	APlayer_Base* MyPlayer = Cast<APlayer_Base>(MeshComp->GetOwner());
	if (MyPlayer == nullptr) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	TArray<AActor*> OutActors;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreActors.Add(MyPlayer);
	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(MeshComp->GetWorld(), Pos, Radius, ObjectTypes, nullptr, IgnoreActors, OutActors);
	if (IsOverlapped)
	{
		for (AActor* OutActor : OutActors)
		{
			float DamagePower = DamageStatic + (MyPlayer->GetCharacterStat()->GetDamage() * DamageMul);
			UE_LOG(LogClass, Warning, TEXT("ApplyDamage : %f"), DamagePower);
			UGameplayStatics::ApplyDamage(OutActor, DamagePower, MyPlayer->GetController(), nullptr, NULL);
		}
	}
}

FString UAnimNotify_AttackHitCheck::GetNotifyName_Implementation() const
{
	return FString(TEXT("AttackHitCheck"));
}
