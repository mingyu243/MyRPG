#include "Enemy_AC.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AEnemy_AC::Key_HomePos(TEXT("HomePos"));
const FName AEnemy_AC::Key_PatrolPos(TEXT("PatrolPos"));
const FName AEnemy_AC::Key_Target(TEXT("Target"));

AEnemy_AC::AEnemy_AC()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/Blueprints/Enemy/AI/BB_Enemy.BB_Enemy'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/Blueprints/Enemy/AI/BT_Enemy.BT_Enemy'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AEnemy_AC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void AEnemy_AC::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AEnemy_AC::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent == nullptr) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
